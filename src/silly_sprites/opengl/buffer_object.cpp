#include "buffer_object.hpp"

namespace sly::gl {
    void BufferObject::init() {
        generate_vertex_array();
        generate_vertex_buffer();
        generate_element_buffer();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);
    }

    void BufferObject::generate_vertex_array() {
        glGenVertexArrays(1, &m_vao);
        bind_vertex_array();
    }

    void BufferObject::generate_vertex_buffer() {
        glGenBuffers(1, &m_vbo);
        bind_vertex_buffer();
        data_vertex_buffer();
    }

    void BufferObject::generate_element_buffer() {
        glGenBuffers(1, &m_ebo);
        bind_element_buffer();
        data_element_buffer();
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

    void BufferObject::data_vertex_buffer() const {
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * m_points.size()), m_points.data(), GL_STATIC_DRAW);
    }

    void BufferObject::data_element_buffer() const {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(unsigned int) * m_indices.size()), m_indices.data(), GL_STATIC_DRAW);
    }

    BufferObject::BufferObject(Points points, Indices indices) : m_points{ points }, m_indices{ indices } {
        init();
    }

    BufferObject::~BufferObject() {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void BufferObject::bind() const {
        glBindVertexArray(m_vao);
    }

    void BufferObject::unbind() const {
        glBindVertexArray(0);
    }

    void BufferObject::draw() const {
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    }

    BufferObject::Points BufferObject::get_points() const {
        return m_points;
    }

    void BufferObject::set_points(Points points) {
        m_points = points;
        bind_vertex_buffer();
        data_vertex_buffer();
    }

    BufferObject::Indices BufferObject::get_indices() const {
        return m_indices;
    }

    void BufferObject::set_indices(Indices indices) {
        m_indices = indices;
        bind_element_buffer();
        data_element_buffer();
    }
} // namespace sly::gl
