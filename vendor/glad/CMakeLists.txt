add_library(glad
        STATIC
        gl.c
        include/glad/gl.h
        include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
