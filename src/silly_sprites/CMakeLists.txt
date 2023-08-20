include(${CMAKE_SOURCE_DIR}/cmake/system_link.cmake)
include(${CMAKE_SOURCE_DIR}/project_options.cmake)

add_library(sillysprites
        STATIC
        include/magic_enum_wrapper.hpp
        include/silly_sprites.hpp
        application.hpp
        silly_sprites.cpp
        application.cpp
        stopwatch.cpp
        stopwatch.hpp
        include/gl_initialize.hpp
        opengl/initialize.cpp
        opengl/error.hpp
        opengl/window.hpp
        opengl/window.cpp
        opengl/glfw_context.cpp
        opengl/glfw_context.hpp
        types.hpp
        input.hpp
        input.cpp
        game_object_and_scene.hpp
        native_script.hpp
        transform.hpp
        time.hpp
        script/engine.cpp
        script/engine.hpp
        script/builtins.hpp
        script/builtins.cpp
        utils.cpp
        script/module.cpp
        script/module.hpp
        script/class_info.hpp
        script.hpp
        app_context.hpp
        script/class_info.cpp
        script/object.hpp
        script/function.hpp
)

setup_dependencies()

target_link_libraries(sillysprites
        PRIVATE project_options
)

target_link_system_libraries(sillysprites
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE glm::glm
        PRIVATE tl::optional
        PRIVATE tl::expected
        PRIVATE spdlog::spdlog
        PRIVATE EnTT::EnTT
        PRIVATE glfw
        PRIVATE Microsoft.GSL::GSL
        PRIVATE glad
        PRIVATE magic_enum::magic_enum
        PRIVATE angelscript
        PRIVATE angelscript_scriptstdstring
        PRIVATE angelscript_scriptbuilder
        PRIVATE angelscript_datetime
        PRIVATE angelscript_math
        PRIVATE angelscript_array
)

target_include_directories(sillysprites
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
