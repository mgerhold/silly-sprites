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
        opengl/gl_initialize.cpp
        opengl/gl_error.hpp
        opengl/gl_error.cpp
        opengl/gl_window.hpp
        opengl/gl_window.cpp
)

include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage("gh:nlohmann/json@3.10.5")
CPMAddPackage("gh:g-truc/glm#0.9.9.8")
CPMAddPackage("gh:TartanLlama/optional@1.1.0")
CPMAddPackage("gh:TartanLlama/expected@1.1.0")
CPMAddPackage("gh:gabime/spdlog@1.12.0")
CPMAddPackage("gh:skypjack/entt@3.12.2")
CPMAddPackage("gh:google/googletest@1.13.0")
CPMAddPackage("gh:microsoft/GSL@4.0.0")
CPMAddPackage("gh:Neargye/magic_enum@0.9.3")
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
        gtest
        gtest_main
        Microsoft.GSL::GSL
        glad
        magic_enum::magic_enum
)

target_include_directories(sillysprites PUBLIC ${CMAKE_SOURCE_DIR}/src/silly_sprites/include)
