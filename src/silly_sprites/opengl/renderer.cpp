#include "renderer.hpp"
#include "buffer_object.hpp"
#include "shader_program.hpp"
#include "vertex.hpp"
#include <gsl/gsl>

// clang-format off
static void flush(
    sly::gl::BufferObject& buffer_object,
    std::vector<sly::gl::Vertex>& vertices,
    std::vector<GLuint>& indices
) {
    // clang-format on
    buffer_object.set_data(vertices, indices);
    buffer_object.draw();
    vertices.clear();
    indices.clear();
}

namespace sly::gl {
    struct Command {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
        ShaderProgram* shader_program;
    };

    Renderer::Renderer() : m_buffer_object{ std::make_unique<BufferObject>() } { }

    Renderer::~Renderer() = default;

    void Renderer::start_frame() {
        glClear(GL_COLOR_BUFFER_BIT);
        m_command_buffer.clear();
    }

    void Renderer::draw_quad(glm::vec2 const position, glm::vec2 const scale, ShaderProgram& shader_program) {
        draw_quad(position, 0.0f, scale, shader_program);
    }

    void Renderer::draw_quad(
            glm::vec2 const position,
            float const rotation,
            glm::vec2 const scale,
            ShaderProgram& shader_program
    ) {
        m_command_buffer.emplace_back(position, rotation, scale, &shader_program);
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

        auto vertices = std::vector<Vertex>{};
        auto indices = std::vector<GLuint>{};

        for (auto const& command : m_command_buffer) {
            if (command.shader_program->m_program_name != current_shader->m_program_name) {
                flush(*m_buffer_object, vertices, indices);
                current_shader = command.shader_program;
                current_shader->bind();
            }

            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 0);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 1);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 2);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 2);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 1);
            indices.push_back(gsl::narrow_cast<GLuint>(vertices.size()) + 3);

            auto const scale = glm::vec3{ command.scale.x, command.scale.y, 1.0f };

            auto positions = std::array<glm::vec3, 4>{
                glm::vec3{ -0.5f, -0.5f, 0.0f },
                glm::vec3{ +0.5f, -0.5f, 0.0f },
                glm::vec3{ -0.5f, +0.5f, 0.0f },
                glm::vec3{ +0.5f, +0.5f, 0.0f },
            };

            auto const radius = glm::sqrt(2.0f * 0.5f * 0.5f);
            for (auto& position : positions) {
                auto const new_position = glm::vec3{
                    radius * (glm::cos(command.rotation) * position.x - glm::sin(command.rotation) * position.y)
                            + command.position.x,
                    radius * (glm::sin(command.rotation) * position.x + glm::cos(command.rotation) * position.y)
                            + command.position.y,
                    0.0f
                };

                vertices.emplace_back(new_position * scale);
            }
        }
        flush(*m_buffer_object, vertices, indices);
    }
} // namespace sly::gl
