#pragma once
#include "Vertex Buffer.hpp"
#include "Vertex Buffer Layout.hpp"
#include "Index Buffer.hpp"

namespace hv {
	class VertexArray {
	public:
		VertexArray(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, const IndexBuffer* indexBuffer = nullptr);

		VertexArray();

		~VertexArray();

		void AppendBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, const IndexBuffer* indexBuffer = nullptr);

		void Bind() const;
		void Unbind() const;

		const IndexBuffer* GetIndexBuffer() const;

	private:
		uint32_t m_id = 0;

		const IndexBuffer* m_indexBuffer = nullptr;

		void Create(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	};
}