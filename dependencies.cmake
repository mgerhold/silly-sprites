include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/system_link.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/angelscript_addons.cmake")

function(setup_dependencies)
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
    CPMAddPackage(
            NAME ANGELSCRIPT
            GITHUB_REPOSITORY codecat/angelscript-mirror
            GIT_TAG 957eac4
            SOURCE_SUBDIR sdk/angelscript/projects/cmake
    )

    setup_angelscript_addon_dependencies()
endfunction()
