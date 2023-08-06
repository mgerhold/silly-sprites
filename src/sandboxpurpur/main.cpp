#define GLFW_INCLUDE_NONE

#include "../silly_sprites/input.hpp"
#include "../silly_sprites/opengl/window.hpp"
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

int main() {
    auto window = sly::gl::Window::create(800, 600);

    if (not window.has_value()) {
        spdlog::critical(magic_enum::enum_name(window.error()));
        return 0;
    }

    // wrap this in some kind of rendering class
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);

    while (not window->should_close()) {
        // wrap this in some kind of rendering class
        glClear(GL_COLOR_BUFFER_BIT);

        window->swap_buffers();
        glfwPollEvents();
        sly::Input::update(window.value());
    }
}

unsigned int set_points() {
    float points[]{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    unsigned int vertex_shader{ glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertex_shader, 1, &example_vertex_shader, NULL);
    glCompileShader(vertex_shader);

    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (not success) {
        char message[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, message);
        spdlog::critical("ERROR::SHADER::VERTEX::COMPILATION_FAILED -> {}\n", message);
    }

    unsigned fragment_shader { glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragment_shader, 1, &example_fragment_shader, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(not success) {
        char message[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, message);
        spdlog::critical("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED -> {}\n", message);
    }

    unsigned int shader_program{ glCreateProgram() };
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (not success) {
        char message[512];
        glGetProgramInfoLog(shader_program, 512, NULL, message);
        spdlog::critical("ERROR::PROGRAMM::LINK_FAILED -> {}\n", message);
    }

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}
