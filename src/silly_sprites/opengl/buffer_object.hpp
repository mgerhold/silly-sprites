#pragma once

#include "../types.hpp"
#include <glad/gl.h>
#include <vector>

namespace sly::gl {
    class BufferObject final {
    private:
        using Points = std::vector<float>;
        using Indices = std::vector<GLuint>;

        GLuint m_vao, m_vbo, m_ebo;

        Points m_points;
        Indices m_indices;

        void init();
        void generate_vertex_array();
        void generate_vertex_buffer();
        void generate_element_buffer();
        void bind_vertex_array() const;
        void bind_vertex_buffer() const;
        void bind_element_buffer() const;
        void data_vertex_buffer() const;
        void data_element_buffer() const;

    public:
        BufferObject(Points points, Indices indices);
        ~BufferObject();

        void bind() const;
        void unbind() const;

        void draw() const;

        [[nodiscard]] Points get_points() const;
        void set_points(Points points);

        [[nodiscard]] Indices get_indices() const;
        void set_indices(Indices indices);
    };
} // namespace sly::gl
