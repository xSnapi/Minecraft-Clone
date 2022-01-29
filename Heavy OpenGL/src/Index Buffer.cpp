#include <hvpch.h>
#include "Index Buffer.hpp"

namespace hv {
	IndexBuffer::IndexBuffer(const void* data, uint32_t bytes) {
		Append(data, bytes);
	}

	IndexBuffer::IndexBuffer() {

	}

	IndexBuffer::~IndexBuffer() {
		if(m_id)
			glDeleteBuffers(1, &m_id);
	}

	void IndexBuffer::Append(const void* data, uint32_t bytes) {
		m_size = bytes;

		Create(data);
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t IndexBuffer::Size() const {
		return m_size;
	}

	void IndexBuffer::Create(const void* data) {
		glGenBuffers(1, &m_id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}
}