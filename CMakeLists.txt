cmake_minimum_required(VERSION 3.26)

project(sillysprites
        VERSION 0.0.1
        DESCRIPTION "a 2D game engine written in C++"
        HOMEPAGE_URL "https://github.com/mgerhold/silly-sprites/"
        LANGUAGES C CXX  # C is required by some of the dependencies
)

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed")
endif ()

# the value of CMAKE_CXX_STANDARD serves as a default for all subsequent targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# don't allow the usage of compiler-specific extensions to improve portability
set(CMAKE_CXX_EXTENSIONS OFF)

# activate LTO (link-time optimizations) to increase the chance of catching ODR violations
include(cmake/lto.cmake)
try_enable_link_time_optimizations()

add_subdirectory(doc)
add_subdirectory(src bin)
add_subdirectory(test)
add_subdirectory(vendor)
