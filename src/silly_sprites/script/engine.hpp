#pragma once

#include "function.hpp"
#include "module.hpp"
#include "object.hpp"
#include "types.hpp"
#include "utils.hpp"
#include <angelscript.h>
#include <cassert>
#include <exception>
#include <filesystem>
#include <fstream>
#include <gsl/gsl>
#include <initializer_list>
#include <scriptbuilder.h>
#include <string>
#include <tl/optional.hpp>

namespace sly::script {

    class EngineError : public std::exception {
    public:
        enum class Type {
            FailedToCreateScriptEngine,
            FailedToRegisterMessageCallback,
            FailedToRegisterBuiltinFunction,
            FailedToCreateNewModule,
            FailedToReadSourceFile,
            CompilationError,
            UnableToReflectOnMissingModule,
            UnableToCallFunctionOnMissingModule,
            UnableToFindTypeInfoOnMissingModule,
            TryingToCallUndeclaredFunction,
            UnableToPassArgument,
            ErrorWhileCallingFunction,
            UnableToRetrieveReturnValue,
            FailedToSetDefaultNamespace,
            FailedToRetrieveTypeIdOfInvalidType,
            FailedToRetrieveTypeInfoOfInvalidType,
            FunctionReturnTypeMismatch,
            FailedToCreateObject,
            MethodNotFoundInClass,
        };

    private:
        Type m_type;

    public:
        explicit EngineError(Type type) : m_type{ type } { }

        [[nodiscard]] char const* what() const override;
    };


    class Engine final {
    private:
        asIScriptEngine* m_engine;
        tl::optional<Module> m_module{ tl::nullopt };
        asIScriptContext* m_context;

    public:
        using MessageCallback = void (*)(asSMessageInfo const*, void*);

    public:
        Engine();
        explicit Engine(MessageCallback message_callback);
        Engine(Engine const&) = delete;
        Engine(Engine&& other) noexcept;
        ~Engine();

        Engine& operator=(Engine const&) = delete;
        Engine& operator=(Engine&& other) noexcept;

        [[nodiscard]] ClassInfoRange classes() const;

        Object create_object(std::string_view type_declaration);
        [[nodiscard]] tl::optional<Function>
        get_class_method(std::string_view class_name, std::string_view method_declaration) const;

        void create_module(std::string_view const name, auto&&... filenames) {
            assert(m_engine != nullptr);
            auto builder = CScriptBuilder{};
            if (builder.StartNewModule(m_engine, name.data()) < 0) {
                throw EngineError{ EngineError::Type::FailedToCreateNewModule };
            }

            (
                    [&]() {
                        auto source = read_file(filenames);
                        if (not source.has_value()) {
                            throw EngineError{ EngineError::Type::FailedToReadSourceFile };
                        }
                        if (builder.AddSectionFromMemory(
                                    filenames, source->c_str(), gsl::narrow_cast<unsigned int>(source->length())
                            )
                            < 0) {
                            throw EngineError{ EngineError::Type::CompilationError };
                        }
                    }(),
                    ...
            );

            if (builder.BuildModule() < 0) {
                throw EngineError{ EngineError::Type::CompilationError };
            }

            auto const module = builder.GetModule();
            m_module = Module{ module };
        }

        template<typename Result = void>
        auto call_method(Object object, Function method, auto&&... arguments) {
            assert(m_context != nullptr);
            return call<Result>(method, object, std::forward<decltype(arguments)>(arguments)...);
        }

        template<typename Result = void>
        auto call_function(std::string_view const function_name, auto&&... arguments) {
            if (not m_module.has_value()) {
                throw EngineError{ EngineError::Type::UnableToCallFunctionOnMissingModule };
            }

            auto const function = m_module->m_module->GetFunctionByName(function_name.data());
            if (function == nullptr) {
                throw EngineError{ EngineError::Type::TryingToCallUndeclaredFunction };
            }

            return call<Result>(Function{ function }, tl::nullopt, std::forward<decltype(arguments)>(arguments)...);
        }

        template<typename Result = void>
        auto call_function(Function function, auto&&... arguments) {
            return call<Result>(function, tl::nullopt, std::forward<decltype(arguments)>(arguments)...);
        }

    private:
        template<typename Result = void>
        auto call(Function const function, tl::optional<Object> const object, auto&&... arguments) {
            auto const actual_return_type_id = function.m_function->GetReturnTypeId();
            auto const expected_return_type_id = get_type_id<Result>();
            if (actual_return_type_id != expected_return_type_id) {
                throw EngineError{ EngineError::Type::FunctionReturnTypeMismatch };
            }

            assert(m_context != nullptr);
            m_context->Prepare(function.m_function);

            if (object.has_value()) {
                m_context->SetObject(object->m_object);
            }

            if constexpr (sizeof...(arguments) > 0) {
                pass_arguments(std::forward<decltype(arguments)>(arguments)...);
            }

            if (m_context->Execute() != asEXECUTION_FINISHED) {
                throw EngineError{ EngineError::Type::ErrorWhileCallingFunction };
            }

            if constexpr (not std::same_as<Result, void>) {
                return retrieve_returned_value<Result>();
            }
        }

        template<usize index = 0>
        void pass_arguments(auto&& first_argument, auto&&... arguments) {
            assert(m_context != nullptr);
            // primitive types
            if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, u8> or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i8>) {
                static_assert(sizeof(asBYTE) == sizeof(u8));
                static_assert(sizeof(asBYTE) == sizeof(i8));
                if (m_context->SetArgByte(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, u16> or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i16>) {
                static_assert(sizeof(asWORD) == sizeof(u16));
                static_assert(sizeof(asWORD) == sizeof(i16));
                if (m_context->SetArgWord(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, u32> or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i32>) {
                static_assert(sizeof(asDWORD) == sizeof(u32));
                static_assert(sizeof(asDWORD) == sizeof(i32));
                if (m_context->SetArgDWord(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, u64> or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i64>) {
                static_assert(sizeof(asQWORD) == sizeof(u64));
                static_assert(sizeof(asQWORD) == sizeof(i64));
                if (m_context->SetArgQWord(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, float>) {
                if (m_context->SetArgFloat(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, double>) {
                if (m_context->SetArgDouble(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            }
            // string
            else if constexpr (std::same_as<std::remove_cvref_t<decltype(first_argument)>, std::string>) {
                if (m_context->SetArgObject(index, &first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            }
            // pointers
            else if constexpr (
                    // clang-format off
                    std::same_as<std::remove_cvref_t<decltype(first_argument)>, u8*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i8*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, u16*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i16*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, u32*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i32*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, u64*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, i64*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, float*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, double*>
                    or std::same_as<std::remove_cvref_t<decltype(first_argument)>, std::string*>
                    // clang-format on
            ) {
                static_assert(sizeof(asBYTE) == sizeof(u8));
                static_assert(sizeof(asBYTE) == sizeof(i8));
                static_assert(sizeof(asWORD) == sizeof(u16));
                static_assert(sizeof(asWORD) == sizeof(i16));
                static_assert(sizeof(asDWORD) == sizeof(u32));
                static_assert(sizeof(asDWORD) == sizeof(i32));
                static_assert(sizeof(asQWORD) == sizeof(u64));
                static_assert(sizeof(asQWORD) == sizeof(i64));
                if (m_context->SetArgAddress(index, first_argument) < 0) {
                    throw EngineError{ EngineError::Type::UnableToPassArgument };
                }
            } else {
                static_assert(dependent_false<index>);
            }

            if constexpr (sizeof...(arguments) > 0) {
                pass_arguments<index + 1>(std::forward<decltype(arguments)>(arguments)...);
            }
        }

        template<typename T>
        [[nodiscard]] auto retrieve_returned_value() {
            assert(m_context != nullptr);
            if constexpr (std::same_as<T, u8> or std::same_as<T, i8>) {
                static_assert(sizeof(asBYTE) == sizeof(u8));
                static_assert(sizeof(asBYTE) == sizeof(i8));
                return m_context->GetReturnByte();
            } else if constexpr (std::same_as<T, u16> or std::same_as<T, i16>) {
                static_assert(sizeof(asWORD) == sizeof(u16));
                static_assert(sizeof(asWORD) == sizeof(i16));
                return m_context->GetReturnWord();
            } else if constexpr (std::same_as<T, u32> or std::same_as<T, i32>) {
                static_assert(sizeof(asDWORD) == sizeof(u32));
                static_assert(sizeof(asDWORD) == sizeof(i32));
                return m_context->GetReturnDWord();
            } else if constexpr (std::same_as<T, u64> or std::same_as<T, i64>) {
                static_assert(sizeof(asQWORD) == sizeof(u64));
                static_assert(sizeof(asQWORD) == sizeof(i64));
                return m_context->GetReturnQWord();
            } else {
                static_assert(type_dependent_false<T>);
            }
        }

        void register_builtin_functions();

        [[nodiscard]] int get_type_id_by_declaration(std::string_view const declaration) {
            auto const type_id = m_engine->GetTypeIdByDecl(declaration.data());
            if (type_id < 0) {
                throw EngineError{ EngineError::Type::FailedToRetrieveTypeIdOfInvalidType };
            }
            return type_id;
        }

        template<typename T>
        [[nodiscard]] int get_type_id() {
            if constexpr (std::same_as<std::remove_cvref_t<T>, void>) {
                return get_type_id_by_declaration("void");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, u8>) {
                return get_type_id_by_declaration("uint8");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, u16>) {
                return get_type_id_by_declaration("uint16");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, u32>) {
                return get_type_id_by_declaration("uint");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, u64>) {
                return get_type_id_by_declaration("uint64");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, i8>) {
                return get_type_id_by_declaration("int8");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, i16>) {
                return get_type_id_by_declaration("int16");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, i32>) {
                return get_type_id_by_declaration("int");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, i64>) {
                return get_type_id_by_declaration("int64");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, float>) {
                return get_type_id_by_declaration("float");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, double>) {
                return get_type_id_by_declaration("double");
            } else if constexpr (std::same_as<std::remove_cvref_t<T>, std::string>) {
                return get_type_id_by_declaration("string");
            } else {
                static_assert(type_dependent_false<T>);
            }
        }

        [[nodiscard]] tl::optional<asITypeInfo*> get_type_info(std::string_view declaration) const;
    };

} // namespace sly::script
