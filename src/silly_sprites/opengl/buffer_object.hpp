#pragma once

#include "../types.hpp"
#include <glad/gl.h>
#include <vector>

namespace sly::gl {
    class BufferObject final {
    private:
        using Points = std::vector<GLfloat>;
        using Indices = std::vector<GLuint>;

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

        void set_points(Points const& points);
        void set_indices(Indices const& indices);
        void set_initial_data(Points const& ponits, Indices const& indices);
    };
} // namespace sly::gl
