#include <hvpch.h>
#include "Shape.hpp"

using namespace hv;

Shader* Shape::s_defaultShader;
Shader* Shape::s_circleShader;

namespace
{
	const std::string defaultVertex   = R"(
		#version 450 core

		layout(location = 0) in vec4 position;
		layout(location = 1) in vec2 texCoord;
		layout(location = 2) in vec4 color;
		
		out vec2 i_texCoord;
		out vec4 i_color;
		
		uniform mat4 u_transform;
		uniform mat4 u_projection;
		
		void main() {
			gl_Position = u_projection * u_transform * position;
			i_texCoord  = texCoord;
			i_color		= color;
		}
	)";

	const std::string defaultFragment = R"(
		#version 450 core

		layout(location = 0) out vec4 o_color;
		
		uniform sampler2D texture;
		
		in vec2 i_texCoord;
		in vec4 i_color;
		
		void main() {
		    vec4 pixel = texture2D(texture, i_texCoord);
			o_color	   = i_color;
		}
	)";

	const std::string circleVertex = R"(
		#version 450 core

		layout(location = 0) in vec4 position;
		layout(location = 1) in vec2 texCoord;
		layout(location = 2) in vec4 color;
		
		out vec2 i_texCoord;
		out vec4 i_color;
		
		uniform mat4 u_transform;
		uniform mat4 u_projection;
		
		void main() {
			gl_Position = u_projection * u_transform * position;
			i_texCoord  = texCoord;
			i_color		= color;
		}
	)";

	// TODO: Write shader for circles
	const std::string circleFragment = R"(
		#version 450 core

		layout(location = 0) out vec4 o_color;
		
		uniform sampler2D texture;
		
		uniform float u_radius;

		in vec2 i_texCoord;
		in vec4 i_color;
		
		void main() {
		    vec4 pixel = texture2D(texture, i_texCoord);
			o_color	   = i_color;
		}
	)";
}

void Shape::Init(glm::mat4 projection) {
	LoadShaders();

	s_defaultShader->SetUniformMat4("u_projection", projection);
	s_circleShader->SetUniformMat4("u_projection", projection);
}

Shape::Shape() 
	: m_position (0.0f, 0.0f)
	, m_origin   (0.0f, 0.0f)
	, m_scale	 (1.0f, 1.0f)
	, m_color	 (1.0f, 1.0f, 1.0f, 1.0f)
	, m_texCoords(0.0f, 0.0f, 0.0f, 0.0f)
	, m_rotation (0.0f)
{
	
}

Shape::~Shape() {

}

void Shape::SetRotation(float rotation) {
	m_rotation = rotation;
}

void Shape::SetPosition(glm::vec2 position) {
	m_position = position;
}

void Shape::SetScale(glm::vec2 scale){
	m_scale = scale;
}

void Shape::SetOrigin(glm::vec2 origin) {
	if (m_origin != origin) {
		m_origin = origin;
		RecreateVertices();
	}
}

void Shape::SetColor(glm::vec4 color) {
	if (m_color != color) {
		m_color = color;
		RecreateVertices();
	}
}

void Shape::SetTexCoords(glm::vec4 texCoords) {
	m_texCoords = texCoords;
}

glm::vec4 Shape::GetTexCoords() const {
	return m_texCoords;
}

glm::vec4 Shape::GetColor() const {
	return m_color;
}

glm::vec2 Shape::GetOrigin() const {
	return m_origin;
}

glm::vec2 Shape::GetScale() const {
	return m_scale;
}

glm::vec2 Shape::GetPosition() const {
	return m_position;
}

float Shape::GetRotation() const {
	return m_rotation;
}

void Shape::SetTexture(Texture& texture) {
	m_texture = &texture;
}

void Shape::LoadShaders() {
	s_defaultShader = new Shader();
	s_circleShader  = new Shader();

	s_defaultShader->LoadFromMemory(defaultVertex, defaultFragment);
	s_circleShader->LoadFromMemory(circleVertex, circleFragment);
}

void Shape::Draw(RenderTarget& target) {
	glm::mat4 transform(1.0f);

	transform = glm::scale		(transform, glm::vec3(m_scale.x, m_scale.y, 1.0f));
	transform = glm::translate	(transform, glm::vec3(m_position.x, m_position.y, 0.0f));
	transform = glm::rotate		(transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, -1.0f));

	s_defaultShader->SetUniformMat4("u_transform", transform);

	target.Draw(m_vertexArray, Primitives::Triangles, s_defaultShader, m_texture, nullptr, true);
}
