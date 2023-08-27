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
            gl_Position = vec4(aPos.x + 0.3f, aPos.y + 0.4f, aPos.z, 1.0);
        }
    )"
};
static char const* const example_fragment_shader{ R"(
        #version 330 core
        out vec4 FragColor;
        
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }   
    )"
};

unsigned int vao;

sly::gl::ShaderProgram set_points() {
    float points[]{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    sly::gl::ShaderProgram shader_program{ example_vertex_shader, "not compliable", example_fragment_shader };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    return shader_program;
}

int main() {
    auto window = sly::gl::Window::create(800, 600);

    if (not window.has_value()) {
        spdlog::critical(magic_enum::enum_name(window.error()));
        return 0;
    }

    // wrap this in some kind of rendering class
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);


    sly::gl::ShaderProgram shader_program{ set_points() };
    auto watch = sly::StopWatch{};


    while (not window->should_close()) {
        spdlog::info("fps: {}", 1.0 / watch.reset());
        // wrap this in some kind of rendering class
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window->swap_buffers();
        glfwPollEvents();
        sly::Input::update(window.value());
    }
}
