#define GLFW_INCLUDE_NONE

#include "../silly_sprites/input.hpp"
#include "../silly_sprites/opengl/shader_program.hpp"
#include "../silly_sprites/opengl/window.hpp"
#include "../silly_sprites/stopwatch.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>


static char const* const example_vertex_shader{ R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )" };
static char const* const example_fragment_shader{ R"(
        #version 330 core
        out vec4 FragColor;
        
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }   
    )" };

unsigned int vao;
unsigned int vbo;
unsigned int ebo;

void set_points() {

    // clang-format off
    float points[]{
         0.0f,   0.5f, 0.0f, // top
        -0.25f,  0.0f, 0.0f, // mid left
         0.25f,  0.0f, 0.0f, // mit right
        -0.5f,  -0.5f, 0.0f, // bottom left
         0.0f,  -0.5f, 0.0f, // bottom mid
         0.5f,  -0.5f, 0.0f, // bottom right
         /*
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, // top left
        */
    };
    // clang-format on

    unsigned int indices[]{
        0, 1, 2, // top
        1, 3, 4, // bottom left
        2, 4, 5, // bottom right
        /*
        0, 1, 3, // first
        1, 2, 3, // second
        */
    };


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
}

int main() {
    auto window = sly::gl::Window::create(800, 600);

    if (not window.has_value()) {
        spdlog::critical(magic_enum::enum_name(window.error()));
        return 0;
    }

    // wrap this in some kind of rendering class
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);


    sly::gl::ShaderProgram shader_program{ example_vertex_shader, "invalid", example_fragment_shader };
    set_points();
    auto watch = sly::StopWatch{};


    while (not window->should_close()) {
        spdlog::info("fps: {}", 1.0 / watch.reset());
        // wrap this in some kind of rendering class
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window->swap_buffers();
        glfwPollEvents();
        sly::Input::update(window.value());
    }
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vao);
}
