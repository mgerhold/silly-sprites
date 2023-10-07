#pragma once

#include "../types.hpp"
#include <glad/gl.h>
#include <vector>

namespace sly::gl {
    class BufferObject final {
    private:
        using Points = std::vector<GLfloat>;
        using Indices = std::vector<GLuint>;

        GLuint m_vao, m_vbo, m_ebo;
        usize m_index_count;

        void generate_and_bind_vertex_array();
        void generate_and_bind_vertex_buffer(Points const& points);
        void generate_and_bind_element_buffer(Indices const& indices);
        void bind_vertex_array() const;
        void bind_vertex_buffer() const;
        void bind_element_buffer() const;
        void data_vertex_buffer(Points const& points) const;
        void data_element_buffer(Indices const& indices) const;

    public:
        BufferObject(Points const& points, Indices const& indices, GLuint location);
        BufferObject(BufferObject const&) = delete;
        BufferObject(BufferObject&& other) noexcept;
        BufferObject& operator=(BufferObject const&) = delete;
        BufferObject& operator=(BufferObject&& other) noexcept;
        ~BufferObject();

        void bind() const;
        void unbind() const;

        void draw() const;

        void set_points(Points const& points);
        void set_indices(Indices const& indices);
    };
} // namespace sly::gl
