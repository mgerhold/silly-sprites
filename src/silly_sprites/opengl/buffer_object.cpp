#include "buffer_object.hpp"
#include "gsl/gsl"

namespace sly::gl {
    void BufferObject::generate_and_bind_vertex_array() {
        glGenVertexArrays(1, &m_vao);
        bind_vertex_array();
    }

    void BufferObject::generate_and_bind_vertex_buffer(Points const& points) {
        glGenBuffers(1, &m_vbo);
        bind_vertex_buffer();
        data_vertex_buffer(points);
    }

    void BufferObject::generate_and_bind_element_buffer(Indices const& indices) {
        glGenBuffers(1, &m_ebo);
        bind_element_buffer();
        data_element_buffer(indices);
    }

    void BufferObject::bind_vertex_array() const {
        glBindVertexArray(m_vao);
    }

    void BufferObject::bind_vertex_buffer() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    }

    void BufferObject::bind_element_buffer() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }

    void BufferObject::data_vertex_buffer(Points const& points) const {
        glBufferData(
                GL_ARRAY_BUFFER,
                gsl::narrow_cast<GLsizeiptr>(sizeof(float) * points.size()),
                points.data(),
                GL_STATIC_DRAW
        );
    }

    void BufferObject::data_element_buffer(Indices const& indices) const {
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                gsl::narrow_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()),
                indices.data(),
                GL_STATIC_DRAW
        );
    }

    BufferObject::BufferObject(Points const& points, Indices const& indices, GLuint location)
        : m_vao{ 0 },
          m_vbo{ 0 },
          m_ebo{ 0 },
          m_index_count{ indices.size() } {
        generate_and_bind_vertex_array();
        generate_and_bind_vertex_buffer(points);
        generate_and_bind_element_buffer(indices);

        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), nullptr);
        glEnableVertexAttribArray(location);
    }

    BufferObject::BufferObject(BufferObject&& other) noexcept
        : m_vao{ std::exchange(other.m_vao, 0) },
          m_vbo{ std::exchange(other.m_vbo, 0) },
          m_ebo{ std::exchange(other.m_ebo, 0) },
          m_index_count{ std::exchange(other.m_index_count, 0) } { }

    BufferObject& BufferObject::operator=(BufferObject&& other) noexcept {
        std::swap(m_vao, other.m_vao);
        std::swap(m_vbo, other.m_vbo);
        std::swap(m_ebo, other.m_ebo);
        std::swap(m_index_count, other.m_index_count);
        return *this;
    }

    BufferObject::~BufferObject() {
        glDeleteBuffers(1, &m_ebo);
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void BufferObject::bind() const {
        glBindVertexArray(m_vao);
    }

    void BufferObject::unbind() const {
        glBindVertexArray(0);
    }

    void BufferObject::draw() const {
        glDrawElements(GL_TRIANGLES, gsl::narrow_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT, nullptr);
    }

    void BufferObject::set_points(Points const& points) {
        bind_vertex_buffer();
        data_vertex_buffer(points);
    }

    void BufferObject::set_indices(Indices const& indices) {
        m_index_count = indices.size();
        bind_element_buffer();
        data_element_buffer(indices);
    }

} // namespace sly::gl
