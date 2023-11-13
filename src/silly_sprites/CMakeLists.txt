include(${CMAKE_SOURCE_DIR}/cmake/system_link.cmake)
include(${CMAKE_SOURCE_DIR}/project_options.cmake)

add_library(sillysprites
        STATIC
        include/magic_enum_wrapper.hpp
        include/silly_sprites.hpp
        application.hpp
        silly_sprites.cpp
        application.cpp
        event_system.hpp
        event_system.cpp
        events.hpp
        global.hpp
        stopwatch.cpp
        stopwatch.hpp
        types.hpp
        input.hpp
        input.cpp
        game_object_and_scene.hpp
        scene.hpp
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
        script/type_info.hpp
        opengl/error.hpp
        opengl/error.cpp
        opengl/window.hpp
        opengl/window.cpp
        opengl/glfw_context.cpp
        opengl/glfw_context.hpp
        opengl/buffer_object.hpp
        opengl/buffer_object.cpp
        opengl/shader.hpp
        opengl/shader.cpp
        opengl/shader_type.hpp
        opengl/shader_program.hpp
        opengl/shader_program.cpp
        opengl/renderer.cpp
        opengl/renderer.hpp
        opengl/vertex.hpp
)

target_link_libraries(sillysprites
        PRIVATE project_options
)

target_link_system_libraries(sillysprites
        PRIVATE nlohmann_json::nlohmann_json
        PUBLIC glm::glm
        PRIVATE tl::optional
        PRIVATE tl::expected
        PUBLIC spdlog::spdlog
        PRIVATE EnTT::EnTT
        PRIVATE glfw
        PUBLIC Microsoft.GSL::GSL
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
