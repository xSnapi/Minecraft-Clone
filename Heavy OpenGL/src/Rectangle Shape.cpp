#include <hvpch.h>
#include "Rectangle Shape.hpp"

using namespace hv;

RectangleShape::RectangleShape() 
	: m_size(0.0f, 0.0f)
{
	m_vertexBuffer.Allocate(0, sizeof(Vertex2D) * 4, VertexBuffer::Type::Static);

	m_layout.Add(ElementType::Float, 2);
	m_layout.Add(ElementType::Float, 2);
	m_layout.Add(ElementType::Float, 4);

	static uint32_t indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	m_indexBuffer.Allocate(indices, 6);

	m_vertexArray.AppendBuffer(m_vertexBuffer, m_layout, &m_indexBuffer);
}

RectangleShape::~RectangleShape() {

}

void RectangleShape::SetSize(glm::vec2 size) {
	if (m_size != size) {
		m_size = size;
		RecreateVertices();
	}
}

glm::vec2 RectangleShape::GetSize() const {
	return m_size;
}

void RectangleShape::RecreateVertices() {
	Vertex2D* vertices = (Vertex2D*)m_vertexBuffer.Data();

	if (m_origin != glm::vec2(0.0f)) {
		glm::vec2 pos(m_size - m_origin);
		vertices[0] = { glm::vec2(-pos.x, -pos.y), glm::vec2(m_texCoords.x,					m_texCoords.y),					m_color };
		vertices[1] = { glm::vec2( pos.x, -pos.y), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y),					m_color };
		vertices[2] = { glm::vec2( pos.x,  pos.y), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y + m_texCoords.w), m_color };
		vertices[3] = { glm::vec2(-pos.x,  pos.y), glm::vec2(m_texCoords.x,					m_texCoords.y + m_texCoords.w), m_color };
	}
	else {
		vertices[0] = { glm::vec2(0.0f,		0.0f),     glm::vec2(m_texCoords.x,					m_texCoords.y),					m_color };
		vertices[1] = { glm::vec2(m_size.x, 0.0f),     glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y),					m_color };
		vertices[2] = { glm::vec2(m_size.x, m_size.y), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y + m_texCoords.w), m_color };
		vertices[3] = { glm::vec2(0.0f,     m_size.y), glm::vec2(m_texCoords.x,					m_texCoords.y + m_texCoords.w), m_color };
	}
}