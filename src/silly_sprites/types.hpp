#include <cstdint>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace sly {

    using usize = std::size_t;

    [[nodiscard]] inline usize operator""_uz(unsigned long long value) {
        return static_cast<usize>(value);
    }

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    [[nodiscard]] inline u8 operator""_u8(unsigned long long value) {
        return static_cast<u8>(value);
    }

    [[nodiscard]] inline u16 operator""_u16(unsigned long long value) {
        return static_cast<u16>(value);
    }

    [[nodiscard]] inline u32 operator""_u32(unsigned long long value) {
        return static_cast<u32>(value);
    }

    [[nodiscard]] inline u64 operator""_u64(unsigned long long value) {
        return static_cast<u64>(value);
    }

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    [[nodiscard]] inline i8 operator""_i8(unsigned long long value) {
        return static_cast<i8>(value);
    }

    [[nodiscard]] inline i16 operator""_i16(unsigned long long value) {
        return static_cast<i16>(value);
    }

    [[nodiscard]] inline i32 operator""_i32(unsigned long long value) {
        return static_cast<i32>(value);
    }

    [[nodiscard]] inline i64 operator""_i64(unsigned long long value) {
        return static_cast<i64>(value);
    }

    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Quaternion = glm::quat;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;

    inline std::ostream& operator<<(std::ostream& ostream, Vec2 vec) {
        return ostream << glm::to_string(vec);
    }

    inline std::ostream& operator<<(std::ostream& ostream, Vec3 vec) {
        return ostream << glm::to_string(vec);
    }

    inline std::ostream& operator<<(std::ostream& ostream, Quaternion quaternion) {
        return ostream << glm::to_string(quaternion);
    }

    inline std::ostream& operator<<(std::ostream& ostream, Mat3 matrix) {
        return ostream << glm::to_string(matrix);
    }

    inline std::ostream& operator<<(std::ostream& ostream, Mat4 matrix) {
        return ostream << glm::to_string(matrix);
    }

} // namespace sly
