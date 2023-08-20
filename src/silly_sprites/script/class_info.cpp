#include "class_info.hpp"

#include <angelscript.h>

namespace sly::script {
    [[nodiscard]] std::string_view ClassInfo::name() const {
        return m_type_info->GetName();
    }

    [[nodiscard]] ClassInfo ClassInfoIterator::operator*() const {
        return ClassInfo{ m_module->GetObjectTypeByIndex(m_next_index) };
    }

    ClassInfoIterator& ClassInfoIterator::operator++() {
        ++m_next_index;
        return *this;
    }

    ClassInfoIterator ClassInfoIterator::operator++(int) {
        auto result = *this;
        ++(*this);
        return result;
    }

    [[nodiscard]] bool ClassInfoIterator::operator==(Sentinel) const {
        return m_next_index >= m_count;
    }

    [[nodiscard]] ClassInfoIterator ClassInfoRange::begin() const {
        return ClassInfoIterator{ m_module, m_module->GetObjectTypeCount() };
    }

    [[nodiscard]] ClassInfoIterator ClassInfoRange::cbegin() const {
        return begin();
    }

    [[nodiscard]] ClassInfoIterator::Sentinel ClassInfoRange::end() const {
        return {};
    }

    [[nodiscard]] ClassInfoIterator::Sentinel ClassInfoRange::cend() const {
        return end();
    }
} // namespace sly::script
