include(${CMAKE_SOURCE_DIR}/cmake/system_link.cmake)

add_executable(sandboxpurpur main.cpp)

target_link_libraries(sandboxpurpur PRIVATE sillysprites)

target_link_system_libraries(sandboxpurpur
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
