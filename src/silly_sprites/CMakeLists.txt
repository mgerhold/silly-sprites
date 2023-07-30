add_library(sillysprites
        STATIC
        include/magic_enum_wrapper.hpp
        include/silly_sprites.hpp
        application.hpp
        silly_sprites.cpp
        application.cpp
        stopwatch.cpp
        stopwatch.hpp
        scene.cpp
        scene.hpp
        include/gl_initialize.hpp
        opengl/initialize.cpp
        opengl/error.hpp
        opengl/window.hpp
        opengl/window.cpp
        opengl/glfw_context.cpp
        opengl/glfw_context.hpp
        types.hpp
        opengl/input.h
        opengl/input.cpp
)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME NLOHMANN_JSON
        GITHUB_REPOSITORY nlohmann/json
        VERSION 3.10.5
        OPTIONS
        "JSON_BuildTests OFF"
        "JSON_CI OFF"
)
CPMAddPackage("gh:g-truc/glm#0.9.9.8")
CPMAddPackage(
        NAME TL_OPTIONAL
        GITHUB_REPOSITORY TartanLlama/optional
        VERSION 1.1.0
        OPTIONS
        "OPTIONAL_BUILD_TESTS OFF"
        "OPTIONAL_BUILD_PACKAGE OFF"
        "DPKG_BUILDPACKAGE_FOUND OFF"
        "OPTIONAL_BUILD_PACKAGE OFF"
        "RPMBUILD_FOUND OFF"
        "OPTIONAL_BUILD_PACKAGE OFF"
        "CMAKE_HOST_WIN32 OFF"
)
CPMAddPackage(
        NAME TL_EXPECTED
        GITHUB_REPOSITORY TartanLlama/expected
        VERSION 1.1.0
        OPTIONS
        "EXPECTED_BUILD_TESTS OFF"
        "EXPECTED_BUILD_PACKAGE_DEB OFF"
)
CPMAddPackage(
        NAME SPDLOG
        GITHUB_REPOSITORY gabime/spdlog
        VERSION 1.12.0
        OPTIONS
        "SPDLOG_BUILD_EXAMPLE OFF"
        "SPDLOG_BUILD_TESTS OFF"
)
CPMAddPackage(
        NAME ENTT
        GITHUB_REPOSITORY skypjack/entt
        VERSION 3.12.2
        OPTIONS
        "ENTT_USE_SANITIZER ON"
        "ENTT_BUILD_TESTING OFF"
        "ENTT_BUILD_DOCS OFF"
)
CPMAddPackage(
        NAME GSL
        GITHUB_REPOSITORY microsoft/GSL
        VERSION 4.0.0
        OPTIONS
        "GSL_TEST OFF"
)
CPMAddPackage(
        NAME MAGIC_ENUM
        GITHUB_REPOSITORY Neargye/magic_enum
        VERSION 0.9.3
        OPTIONS
        "MAGIC_ENUM_OPT_BUILD_EXAMPLES OFF"
        "MAGIC_ENUM_OPT_BUILD_TESTS OFF"
)
CPMAddPackage(
        NAME GLFW
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.8
        OPTIONS
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BULID_DOCS OFF"
)

target_link_libraries(sillysprites
        nlohmann_json::nlohmann_json
        glm::glm
        tl::optional
        tl::expected
        spdlog::spdlog
        EnTT::EnTT
        glfw
        Microsoft.GSL::GSL
        glad
        magic_enum::magic_enum
)

target_include_directories(sillysprites
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
