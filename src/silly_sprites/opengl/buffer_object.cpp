#include "buffer_object.hpp"
#include "gsl/gsl"

namespace sly::gl {

    BufferObject::BufferObject() {

        glGenVertexArrays(1, &m_vertex_array_object);
        glBindVertexArray(m_vertex_array_object);

        glGenBuffers(1, &m_vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);

        glGenBuffers(1, &m_element_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object);


        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                3 * sizeof(GL_FLOAT),
                nullptr
        );                            // todo: allow multiple vertex attributes
        glEnableVertexAttribArray(0); // todo: allow multiple vertex attributes
    }

    BufferObject::BufferObject(BufferObject&& other) noexcept
        : m_vertex_array_object{ std::exchange(other.m_vertex_array_object, 0) },
          m_vertex_buffer_object{ std::exchange(other.m_vertex_buffer_object, 0) },
          m_element_buffer_object{ std::exchange(other.m_element_buffer_object, 0) },
          m_index_count{ std::exchange(other.m_index_count, 0) } { }

    BufferObject& BufferObject::operator=(BufferObject&& other) noexcept {
        if (this == std::addressof(other)) {
            return *this;
        }

        std::swap(m_vertex_array_object, other.m_vertex_array_object);
        std::swap(m_vertex_buffer_object, other.m_vertex_buffer_object);
        std::swap(m_element_buffer_object, other.m_element_buffer_object);
        std::swap(m_index_count, other.m_index_count);
        return *this;
    }

    BufferObject::~BufferObject() {
        glDeleteBuffers(1, &m_element_buffer_object);
        glDeleteBuffers(1, &m_vertex_buffer_object);
        glDeleteVertexArrays(1, &m_vertex_array_object);
    }

    void BufferObject::bind() const {
        glBindVertexArray(m_vertex_array_object);
    }

    void BufferObject::unbind() const {
        glBindVertexArray(0);
    }

    void BufferObject::draw() const {
        bind();
        glDrawElements(GL_TRIANGLES, gsl::narrow_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT, nullptr);
    }

    void BufferObject::set_points(Points const points) {
        bind();
        glBufferData(
                GL_ARRAY_BUFFER,
                gsl::narrow_cast<GLsizeiptr>(points.size_bytes()),
                points.data(),
                GL_DYNAMIC_DRAW
        );
    }

    void BufferObject::set_indices(Indices indices) {
        m_index_count = indices.size();
        bind();
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                gsl::narrow_cast<GLsizeiptr>(indices.size_bytes()),
                indices.data(),
                GL_DYNAMIC_DRAW
        );
    }

    void BufferObject::set_data(Points points, Indices indices) {
        set_points(points);
        set_indices(indices);
    }

} // namespace sly::gl
