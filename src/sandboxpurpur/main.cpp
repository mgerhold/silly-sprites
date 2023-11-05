#define GLFW_INCLUDE_NONE

#include "../silly_sprites/input.hpp"
#include "../silly_sprites/opengl/buffer_object.hpp"
#include "../silly_sprites/opengl/shader_program.hpp"
#include "../silly_sprites/opengl/window.hpp"
#include "../silly_sprites/stopwatch.hpp"
#include "../silly_sprites/types.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>

/*
static char const* const example_vertex_shader{ R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )" };
*/
static char const* const example_vertex_shader{ "              " };
/*
static char const* const example_fragment_shader{ R"(
        #version 330 core
        out vec4 FragColor;
        
        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )"
};
*/
static char const* const example_fragment_shader{ R"(
        #version 330 core
        out vec4 FragColor;
        
        void main()
        
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )" };

static inline std::vector<sly::gl::Vertex> points{
    // clang-format off
    sly::gl::Vertex{ glm::vec3{  0.0f,  0.5f, 0.0f } }, // top
    sly::gl::Vertex{ glm::vec3{ -0.25f, 0.0f, 0.0f } }, // mid left
    sly::gl::Vertex{ glm::vec3{  0.25f, 0.0f, 0.0f } }, // mit right
    sly::gl::Vertex{ glm::vec3{ -0.5f, -0.5f, 0.0f } }, // bottom left
    sly::gl::Vertex{ glm::vec3{  0.0f, -0.5f, 0.0f } }, // bottom mid
    sly::gl::Vertex{ glm::vec3{  0.5f, -0.5f, 0.0f } }, // bottom right
    // clang-format on
};

static inline std::vector<unsigned int> const indices{
    0, 1, 2, // top
    1, 3, 4, // bottom left
    2, 4, 5, // bottom right
};

void move_points_down(sly::gl::BufferObject& buffer) {
    for (auto& vertex : points) {
        vertex.position.y -= 0.01f;
    }

    buffer.set_points(points);
}
void move_points_up(sly::gl::BufferObject& buffer) {
    for (auto& vertex : points) {
        vertex.position.y += 0.01f;
    }

    buffer.set_points(points);
}
void move_points_left(sly::gl::BufferObject& buffer) {
    for (auto& vertex : points) {
        vertex.position.x -= 0.01f;
    }

    buffer.set_points(points);
}
void move_points_right(sly::gl::BufferObject& buffer) {
    for (auto& vertex : points) {
        vertex.position.x += 0.01f;
    }

    buffer.set_points(points);
}

void move_points(sly::gl::BufferObject& buffer) {
    if (sly::Input::is_key_down(sly::Key::Right)) {
        move_points_right(buffer);
    }
    if (sly::Input::is_key_down(sly::Key::Left)) {
        move_points_left(buffer);
    }
    if (sly::Input::is_key_down(sly::Key::Up)) {
        move_points_up(buffer);
    }
    if (sly::Input::is_key_down(sly::Key::Down)) {
        move_points_down(buffer);
    }
}

int main() {
    auto window = sly::gl::Window{ 800, 600 };

    // wrap this in some kind of rendering class
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);


    sly::gl::ShaderProgram shader_program{ example_vertex_shader, example_fragment_shader };
    sly::gl::BufferObject buffer_object{};
    buffer_object.set_data(points, indices);
    // buffer_object.set_points(points);
    // buffer_object.set_indices(indices);
    auto watch = sly::StopWatch{};


    while (not window.should_close()) {
        // spdlog::info("fps: {}", 1.0 / watch.reset());
        // wrap this in some kind of rendering class
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.bind();

        buffer_object.draw();
        buffer_object.unbind();

        window.swap_buffers();
        glfwPollEvents();
        sly::Input::update(window);

        move_points(buffer_object);
    }
}
