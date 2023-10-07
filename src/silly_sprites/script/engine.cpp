#include "engine.hpp"

#include "builtins.hpp"
#include <datetime.h>
#include <magic_enum_wrapper.hpp>
#include <scriptmath.h>
#include <scriptstdstring.h>
#include <spdlog/spdlog.h>
#include <string_view>
#include <utility>

namespace {
    void register_global_function(asIScriptEngine* const engine, std::string_view const declaration, auto function) {
        if (engine->RegisterGlobalFunction(declaration.data(), asFUNCTION(function), asCALL_CDECL) < 0) {
            throw sly::script::EngineError{ sly::script::EngineError::ShaderType::FailedToRegisterBuiltinFunction };
        }
    }

    template<typename Function>
    struct FunctionDeclaration {
        std::string_view declaration;
        Function function;

        FunctionDeclaration(std::string_view const declaration_, Function&& function_)
            : declaration{ declaration_ },
              function{ std::forward<Function>(function_) } { }
    };

    void register_global_functions(
            asIScriptEngine* const engine,
            std::string_view const namespace_,
            auto&&... declarations
    ) {
        auto const previous_namespace = std::string{ engine->GetDefaultNamespace() }; // copy to avoid dangling pointer
        if (engine->SetDefaultNamespace(namespace_.data()) < 0) {
            throw sly::script::EngineError{ sly::script::EngineError::ShaderType::FailedToSetDefaultNamespace };
        }
        register_global_functions(engine, std::forward<decltype(declarations)>(declarations)...);
        if (engine->SetDefaultNamespace(previous_namespace.c_str()) < 0) {
            throw sly::script::EngineError{ sly::script::EngineError::ShaderType::FailedToSetDefaultNamespace };
        }
    }

    void register_global_functions(asIScriptEngine* const engine, auto&&... declarations) {
        ([&]() { register_global_function(engine, declarations.declaration, declarations.function); }(), ...);
    }

    void message_callback(asSMessageInfo const* const message, [[maybe_unused]] void* const parameter) {
        switch (message->type) {
            case asMSGTYPE_ERROR:
                spdlog::error("{}:{}:{}: {}", message->section, message->row, message->col, message->message);
                break;
            case asMSGTYPE_WARNING:
                spdlog::warn("{}:{}:{}: {}", message->section, message->row, message->col, message->message);
                break;
            case asMSGTYPE_INFORMATION:
                spdlog::info("{}:{}:{}: {}", message->section, message->row, message->col, message->message);
                break;
        }
    }
} // namespace

namespace sly::script {

    [[nodiscard]] char const* EngineError::what() const noexcept {
        return magic_enum::enum_name(m_type).data();
    }

    Engine::Engine() : Engine{ message_callback } { }

    Engine::Engine(Engine::MessageCallback message_callback) : m_engine{ asCreateScriptEngine() } {
        if (m_engine == nullptr) {
            throw EngineError{ EngineError::ShaderType::FailedToCreateScriptEngine };
        }

        if (m_engine->SetMessageCallback(asFUNCTION(message_callback), nullptr, asCALL_CDECL) < 0) {
            throw EngineError{ EngineError::ShaderType::FailedToRegisterMessageCallback };
        }

        RegisterStdString(m_engine);
        RegisterScriptMath(m_engine);
        RegisterScriptDateTime(m_engine);

        register_builtin_types();
        register_builtin_functions();

        m_context = m_engine->CreateContext();
    }

    Engine::Engine(Engine&& other) noexcept
        : m_engine{ std::exchange(other.m_engine, nullptr) },
          m_context{ std::exchange(other.m_context, nullptr) } { }

    Engine::~Engine() {
        if (m_engine != nullptr) {
            assert(m_context != nullptr);
            m_context->Release();
            m_context = nullptr;
            m_engine->ShutDownAndRelease();
            m_engine = nullptr;
        }
        assert(m_context == nullptr);
        assert(m_engine == nullptr);
    }

    Engine& Engine::operator=(Engine&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        std::swap(m_engine, other.m_engine);
        return *this;
    }

    [[nodiscard]] ClassInfoRange Engine::classes() const {
        if (not m_module.has_value()) {
            throw EngineError{ EngineError::ShaderType::UnableToReflectOnMissingModule };
        }
        return ClassInfoRange{ m_module.value().m_module };
    }

    Object Engine::create_object([[maybe_unused]] std::string_view const type_declaration) {
        auto type_info = get_type_info(type_declaration);
        if (not type_info.has_value()) {
            throw EngineError{ EngineError::ShaderType::FailedToRetrieveTypeInfoOfInvalidType };
        }

        auto const object_address = m_engine->CreateScriptObject(type_info->m_type_info);
        if (object_address == nullptr) {
            throw EngineError{ EngineError::ShaderType::FailedToCreateObject };
        }

        return Object{ object_address, std::move(*type_info) };
    }

    void Engine::destroy_object(Object const object) {
        m_engine->ReleaseScriptObject(object.m_object, object.m_type.m_type_info);
    }

    [[nodiscard]] tl::optional<Function>
    Engine::get_class_method(std::string_view const class_name, std::string_view const method_declaration) const {
        auto const type_info = get_type_info(class_name);
        if (not type_info.has_value()) {
            return tl::nullopt;
        }

        auto const method = type_info->m_type_info->GetMethodByDecl(method_declaration.data());
        if (method == nullptr) {
            return tl::nullopt;
        }

        return Function{ method };
    }

    void Engine::register_builtin_functions() {
        using namespace std::string_view_literals;
        using namespace sly::script;
        register_global_functions(
                m_engine,
                FunctionDeclaration{ "void print(const string &in text)"sv, &builtins::print },
                FunctionDeclaration{ "void println(const string &in text)"sv, &builtins::println },
                FunctionDeclaration{ "void eprint(const string &in text)"sv, &builtins::eprint },
                FunctionDeclaration{ "void eprintln(const string &in text)"sv, &builtins::eprintln },
                FunctionDeclaration{ "void destroy()"sv, &builtins::destroy }
        );

        register_global_functions(
                m_engine,
                "Log"sv,
                FunctionDeclaration{ "void trace(const string &in text)"sv, &builtins::logging::trace },
                FunctionDeclaration{ "void debug(const string &in text)"sv, &builtins::logging::debug },
                FunctionDeclaration{ "void info(const string &in text)"sv, &builtins::logging::info },
                FunctionDeclaration{ "void warning(const string &in text)"sv, &builtins::logging::warning },
                FunctionDeclaration{ "void warn(const string &in text)"sv, &builtins::logging::warning },
                FunctionDeclaration{ "void error(const string &in text)"sv, &builtins::logging::error },
                FunctionDeclaration{ "void critical(const string &in text)"sv, &builtins::logging::critical }
        );
    }

    void Engine::register_builtin_types() {
        if (m_engine->RegisterObjectType("Time", sizeof(Time), asOBJ_VALUE | asOBJ_POD | asGetTypeTraits<Time>()) < 0) {
            throw EngineError{ EngineError::ShaderType::FailedToRegisterBuiltinType };
        }
        if (m_engine->RegisterObjectProperty("Time", "double elapsed", asOFFSET(Time, elapsed)) < 0) {
            throw EngineError{ EngineError::ShaderType::FailedToRegisterObjectProperty };
        }
        if (m_engine->RegisterObjectProperty("Time", "double delta", asOFFSET(Time, delta)) < 0) {
            throw EngineError{ EngineError::ShaderType::FailedToRegisterObjectProperty };
        }
    }

    [[nodiscard]] tl::optional<TypeInfo> Engine::get_type_info(std::string_view const declaration) const {
        if (not m_module.has_value()) {
            throw EngineError{ EngineError::ShaderType::UnableToFindTypeInfoOnMissingModule };
        }
        auto const type_info = m_module->m_module->GetTypeInfoByDecl(declaration.data());
        if (type_info == nullptr) {
            return tl::nullopt;
        }
        return TypeInfo{ type_info };
    }

} // namespace sly::script
