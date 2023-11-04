#include "renderer.hpp"
#include "buffer_object.hpp"
#include "shader_program.hpp"

#include <gsl/gsl>

static void flush(sly::gl::BufferObject& buffer_object, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {
    buffer_object.set_data(vertices, indices);
    buffer_object.draw();
    vertices.clear();
    indices.clear();
}

namespace sly::gl {
    struct Command {
        glm::vec2 position;
        glm::vec2 scale;
        ShaderProgram* shader_program;
    };

    Renderer::Renderer() : m_buffer_object{ std::make_unique<BufferObject>() } { }

    Renderer::~Renderer() = default;

    void Renderer::start_frame() {
        m_command_buffer.clear();
    }

    void Renderer::draw_quad(glm::vec2 position, glm::vec2 scale, ShaderProgram& shader_program) {
        m_command_buffer.emplace_back(position, scale, &shader_program);
    }

    void Renderer::render() {
        if (m_command_buffer.empty()) {
            return;
        }

        std::sort(m_command_buffer.begin(), m_command_buffer.end(), [](Command const& left, Command const& right) {
            return left.shader_program->m_program_name < right.shader_program->m_program_name;
        });

        auto current_shader = m_command_buffer.front().shader_program;
        current_shader->bind();

        auto vertices = std::vector<GLfloat>{};
        auto indices = std::vector<GLuint>{};

        for (auto const& command : m_command_buffer) {
            if (command.shader_program->m_program_name != current_shader->m_program_name) {
                flush(*m_buffer_object, vertices, indices);
                current_shader = command.shader_program;
                current_shader->bind();
            }

            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3 + 1);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3 + 2);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3 + 2);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3 + 1);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) / 3 + 3);

            vertices.push_back(command.position.x);
            vertices.push_back(command.position.y);
            vertices.push_back(0.0f);

            vertices.push_back(command.position.x + command.scale.x);
            vertices.push_back(command.position.y);
            vertices.push_back(0.0f);

            vertices.push_back(command.position.x);
            vertices.push_back(command.position.y + command.scale.y);
            vertices.push_back(0.0f);

            vertices.push_back(command.position.x + command.scale.x);
            vertices.push_back(command.position.y + command.scale.y);
            vertices.push_back(0.0f);
        }
        flush(*m_buffer_object, vertices, indices);
    }
} // namespace sly::gl
