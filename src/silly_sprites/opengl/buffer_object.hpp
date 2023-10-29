#pragma once

#include "../types.hpp"
#include <glad/gl.h>
#include <span>

namespace sly::gl {
    class BufferObject final {
    private:
        using Points = std::span<GLfloat const>;
        using Indices = std::span<GLuint const>;

        GLuint m_vertex_array_object = 0;
        GLuint m_vertex_buffer_object = 0;
        GLuint m_element_buffer_object = 0;
        usize m_index_count = 0;

    public:
        BufferObject();
        BufferObject(BufferObject const&) = delete;
        BufferObject(BufferObject&& other) noexcept;
        BufferObject& operator=(BufferObject const&) = delete;
        BufferObject& operator=(BufferObject&& other) noexcept;
        ~BufferObject();

        void bind() const;
        void unbind() const;

        void draw() const;

        void set_points(Points points);
        void set_indices(Indices indices);
        void set_data(Points points, Indices indices);
    };
} // namespace sly::gl
