add_library(glad
        STATIC
        gl.c
        include/glad/gl.h
        include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC include)
