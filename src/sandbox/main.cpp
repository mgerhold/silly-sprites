#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <gsl/gsl>
#include <iostream>
#include <magic_enum_wrapper.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <test.hpp>
#include <tl/expected.hpp>
#include <tl/optional.hpp>

enum class Color {
    Red,
    Green,
    Blue,
};

int main() {
    spdlog::info("Hello, world!");
    auto vec = tl::optional<glm::vec3>{
        glm::vec3{1.0, 2.0, 3.0}
    };
    if (vec.has_value()) {
        spdlog::info("{},{},{}", vec->x, vec->y, vec->z);
    }
    auto const value = gsl::narrow_cast<float>(3.14);
    spdlog::info("{}", value);
    spdlog::info("this is just a test!");

    for (auto const color : magic_enum::enum_values<Color>()) {
        spdlog::info("{} is a color", magic_enum::enum_name(color));
    }

    spdlog::info("40 + 2 = {}", add(40, 2));
}
