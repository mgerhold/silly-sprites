#pragma once

#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace sly::gl {

    struct Command;
    class BufferObject;
    class ShaderProgram;

    class Renderer final {
    private:
        std::vector<Command> m_command_buffer;
        std::unique_ptr<BufferObject> m_buffer_object;

    public:
        Renderer();
        Renderer(Renderer const&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(Renderer const&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        ~Renderer();

        void start_frame();

        void draw_quad(glm::vec2 position, glm::vec2 scale, ShaderProgram& shader_program);
        void draw_quad(glm::vec2 position, float rotation, glm::vec2 scale, ShaderProgram& shader_program);

        void render();
    };

} // namespace sly::gl
