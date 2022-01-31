#include <hvpch.h>
#include "Render Target.hpp"

using namespace hv;

namespace
{
	const std::string defaultVertex = R"(
		#version 450 core
		
		layout(location = 0) in vec4 position;
		
		void main() {
			gl_Position = position;
		}
	)";

	const std::string defaultFragment = R"(
		#version 450 core
		
		layout(location = 0) out vec4 o_color;
		
		void main() {
			o_color = vec4(1.0);
		}
	)";
}

Shader* RenderTarget::m_defaultShader = nullptr;

void RenderTarget::Init() {
	if (!m_defaultShader) {
		m_defaultShader = new Shader();
		m_defaultShader->LoadFromMemory(defaultVertex, defaultFragment);
	}
}

RenderTarget::RenderTarget() {

}

RenderTarget::~RenderTarget() {

}

void RenderTarget::Draw(Drawable& drawable, const Shader* shader) {
	if (shader)
		shader->Bind();

	drawable.Draw(*this);
}

void RenderTarget::Draw(const VertexArray& vertexArray, Primitives type, const Shader* shader, const Texture* texture, const IndexBuffer* indexBuffer, bool _2D) {
	vertexArray.Bind();

	if (shader)
		shader->Bind();

	if (texture)
		texture->Bind();

	uint32_t size = 0;

	if (vertexArray.GetIndexBuffer()) {
		size = vertexArray.GetIndexBuffer()->Size();
		vertexArray.GetIndexBuffer()->Bind();
	}
	else {
		size = indexBuffer->Size();
		indexBuffer->Bind();
	}

	HV_DEBUG_ASSERT(size); // Size was 0 

	uint32_t glType = GetGLPrimitive(type);

	if (!_2D)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glDrawElements(glType, size, GL_UNSIGNED_INT, nullptr);
}

uint32_t RenderTarget::GetGLPrimitive(Primitives type) {
	switch (type)
	{
	case Primitives::Triangles:
		return GL_TRIANGLES;
	case Primitives::Lines:
		return GL_LINES;
	case Primitives::Points:
		return GL_POINTS;
	}

	return 0;
}
