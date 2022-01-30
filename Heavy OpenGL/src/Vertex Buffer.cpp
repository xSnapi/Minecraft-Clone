#include <hvpch.h>
#include "Vertex Buffer.hpp"

using namespace hv;

VertexBuffer::VertexBuffer(const void* data, uint32_t size, Type type) {
	Append(data, size, type);
}

VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer() {
	if (m_id)
		glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Append(const void* data, uint32_t size, Type type) {
	m_type = type;

	Create(data, size);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Create(const void* data, uint32_t size) {
	glGenBuffers(1, &m_id);
	Bind();

	int type = GetGLType(m_type);

	if (!type)
		hv::Debug::Log(hv::Color::Red, "[Failed to get vertex buffer type!]");

	glBufferData(GL_ARRAY_BUFFER, size, data, type);
}

int VertexBuffer::GetGLType(Type type) {
	switch (type)
	{
	case Type::Draw:
		return GL_STATIC_DRAW;
	default:
		0;
	}

	return 0;
}
