#include <hvpch.h>
#include "Circle Shape.hpp"

using namespace hv;

CircleShape::CircleShape() 
	: m_radius(0.0f)
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

CircleShape::~CircleShape() {

}

void CircleShape::SetRadius(float radius) {
	if (m_radius != radius) {
		m_radius = radius;
		RecreateVertices();
	}
}

float CircleShape::GetRadius() const {
	return m_radius;
}

void CircleShape::RecreateVertices() {
	Vertex2D* vertices = (Vertex2D*)m_vertexBuffer.Data();


	if (m_origin != glm::vec2(0.0f)) {
		glm::vec2 pos(2.0f * m_radius - m_origin);

		vertices[0] = { glm::vec2(-pos.x, -pos.y), glm::vec2(m_texCoords.x,					m_texCoords.y),					m_color };
		vertices[1] = { glm::vec2( pos.x, -pos.y), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y),					m_color };
		vertices[2] = { glm::vec2( pos.x,  pos.y), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y + m_texCoords.w), m_color };
		vertices[3] = { glm::vec2(-pos.x,  pos.y), glm::vec2(m_texCoords.x,					m_texCoords.y + m_texCoords.w), m_color };
	}
	else {
		float pos = m_radius * 2.0f;

		vertices[0] = { glm::vec2(0.0f,	0.0f), glm::vec2(m_texCoords.x,					m_texCoords.y),					m_color };
		vertices[1] = { glm::vec2(pos,  0.0f), glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y),					m_color };
		vertices[2] = { glm::vec2(pos,  pos),  glm::vec2(m_texCoords.x + m_texCoords.z, m_texCoords.y + m_texCoords.w), m_color };
		vertices[3] = { glm::vec2(0.0f, pos),  glm::vec2(m_texCoords.x,					m_texCoords.y + m_texCoords.w), m_color };
	}

}
