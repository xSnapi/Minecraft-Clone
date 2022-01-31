#include <hvpch.h>
#include "Index Buffer.hpp"

using namespace hv;

IndexBuffer::IndexBuffer(const void* data, uint32_t bytes) {
	Allocate(data, bytes);
}

IndexBuffer::IndexBuffer() {

}

IndexBuffer::~IndexBuffer() {
	if(m_id)
		glDeleteBuffers(1, &m_id);
}

uint8_t* IndexBuffer::Data(uint32_t offset) const {
	Bind();
	uint8_t* buffer = (uint8_t*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	return &buffer[offset];
}

void IndexBuffer::Allocate(const void* data, uint32_t bytes) {
	m_size = bytes;

	Create(data);
}

void IndexBuffer::Reallocate(const void* data, uint32_t bytes, uint32_t offset) {
	HV_DEBUG
	(
		if (bytes + offset > m_size) {
			Debug::Log(Color::Red, "[Failed to realocate Index Buffer defined region of memory extends beyond buffer!]\n");
			return;
		}
	)

	glBufferSubData(m_id, offset, bytes, data);
}

void IndexBuffer::Clear() {
	glInvalidateBufferData(m_id);
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
