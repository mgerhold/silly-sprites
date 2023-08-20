#pragma once

#include <cstdint>
#include <string_view>

class asITypeInfo;
class asIScriptModule;

using asUINT = std::uint32_t;

namespace sly::script {

    class ClassInfo final {
    private:
        asITypeInfo* m_type_info;

        explicit ClassInfo(asITypeInfo* type_info) : m_type_info{ type_info } { }

    public:
        ClassInfo(ClassInfo const&) = delete;
        ClassInfo(ClassInfo&&) = delete;
        ClassInfo& operator=(ClassInfo const&) = delete;
        ClassInfo& operator=(ClassInfo&&) = delete;

        [[nodiscard]] std::string_view name() const;

        friend class ClassInfoIterator;
    };

    class ClassInfoIterator final {
    private:
        asIScriptModule* m_module;
        asUINT m_count;
        asUINT m_next_index{ 0 };

        struct Sentinel { };

        ClassInfoIterator(asIScriptModule* module, asUINT num_class_types)
            : m_module{ module },
              m_count{ num_class_types } { }

    public:
        [[nodiscard]] ClassInfo operator*() const;
        ClassInfoIterator& operator++();
        ClassInfoIterator operator++(int);
        [[nodiscard]] bool operator==(Sentinel) const;

        friend class ClassInfoRange;
    };

    class ClassInfoRange final {
    private:
        asIScriptModule* m_module;

        explicit ClassInfoRange(asIScriptModule* module) : m_module{ module } { }

    public:
        [[nodiscard]] ClassInfoIterator begin() const;
        [[nodiscard]] ClassInfoIterator cbegin() const;
        [[nodiscard]] ClassInfoIterator::Sentinel end() const;
        [[nodiscard]] ClassInfoIterator::Sentinel cend() const;

        friend class Module;
        friend class Engine;
    };

} // namespace sly::script
