#include <hvpch.h>
#include "Vertex Array.hpp"

namespace hv {

	VertexArray::VertexArray(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, const IndexBuffer* indexBuffer) {
		glGenVertexArrays(1, &m_id);

		AppendBuffer(vertexBuffer, layout, indexBuffer);
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray() {
		if(m_id)
			glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::AppendBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, const IndexBuffer* indexBuffer) {
		m_indexBuffer = indexBuffer;

		Create(vertexBuffer, layout);
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_id);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	const IndexBuffer* VertexArray::GetIndexBuffer() const {
		return m_indexBuffer;
	}

	void VertexArray::Create(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) {
		Bind();
		vertexBuffer.Bind();

		const auto& elements = layout.GetElements();

		uint32_t offset = 0;

		for (uint32_t i = 0; i < elements.size(); i++) {
			auto& e = elements[i];

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, e.Size, VertexBufferLayout::Element::GetGLType(e.Type), e.Normalized, layout.GetStride(), (const void*)offset);

			offset += e.Size * VertexBufferLayout::Element::GetTypeSize(e.Type);
		}
	}
}