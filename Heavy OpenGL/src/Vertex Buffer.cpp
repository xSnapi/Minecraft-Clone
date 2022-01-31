#include <hvpch.h>
#include "Vertex Buffer.hpp"

using namespace hv;

VertexBuffer::VertexBuffer(const void* data, uint32_t size, Type type) {
	Allocate(data, size, type);
}

VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer() {
	if (m_id)
		glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Allocate(const void* data, uint32_t size, Type type) {
	m_type = type;

	Create(data, size);
}

uint8_t* VertexBuffer::Data(uint32_t offset) const {
	Bind();
	uint8_t* buffer = (uint8_t*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	return &buffer[offset];
}

void VertexBuffer::Clear() {
	glInvalidateBufferData(m_id);
}

void VertexBuffer::Reallocate(const void* data, uint32_t size, uint32_t offset, Type type) { // Note: offset is value in bytes
	HV_DEBUG
	(
		if (size + offset > m_size) {
			Debug::Log(Color::Red, "[Failed to realocate Vertex Buffer defined region of memory extends beyond buffer!]\n");
			return;
		}
	)

	glBufferSubData(m_id, offset, size, data);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::Type VertexBuffer::GetType() const {
	return m_type;
}

void VertexBuffer::Create(const void* data, uint32_t size) {
	glGenBuffers(1, &m_id);
	Bind();

	int type = GetGLType(m_type);

	if (!type)
		hv::Debug::Log(hv::Color::Red, "[Failed to get vertex buffer type!]");

	m_size = size;

	glBufferData(GL_ARRAY_BUFFER, size, data, type);
}

int VertexBuffer::GetGLType(Type type) {
	switch (type)
	{
	case Type::Static:
		return GL_STATIC_DRAW;
	case Type::Dynamic:
		return GL_STATIC_DRAW;
	default:
		0;
	}

	return 0;
}
