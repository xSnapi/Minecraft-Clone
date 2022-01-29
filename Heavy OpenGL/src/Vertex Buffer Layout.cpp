#include <hvpch.h>
#include "Vertex Buffer Layout.hpp"

namespace hv {
	VertexBufferLayout::VertexBufferLayout() {

	}

	VertexBufferLayout::~VertexBufferLayout() {

	}

	void VertexBufferLayout::Add(ElementType type, uint32_t size, uint8_t normalized) {
		Push(type, size, normalized);
	}

	uint32_t VertexBufferLayout::GetStride() const {
		return m_stride;
	}

	const std::vector<VertexBufferLayout::Element>& VertexBufferLayout::GetElements() const {
		return m_Elements;
	}

	void VertexBufferLayout::Push(ElementType type, uint32_t size, uint8_t normalized) {
		m_Elements.emplace_back(type, size, normalized);

		m_stride += size * Element::GetTypeSize(type);
	}
	
}

namespace hv {
	VertexBufferLayout::Element::Element(ElementType type, uint32_t size, uint8_t normalized) 
		: Type(type)
		, Size(size)
		, Normalized(normalized)
	{

	}

	uint32_t VertexBufferLayout::Element::GetTypeSize(ElementType type) {
		switch (type)
		{
		case ElementType::Float:
			return sizeof(float);

		case ElementType::UInt32:
			return sizeof(uint32_t);

		case ElementType::UInt8:
			return sizeof(uint8_t);
		}

		return 0;
	}

	uint32_t VertexBufferLayout::Element::GetGLType(ElementType type) {
		switch (type)
		{
		case ElementType::Float:
			return GL_FLOAT;

		case ElementType::UInt32:
			return GL_UNSIGNED_INT;

		case ElementType::UInt8:
			return GL_UNSIGNED_BYTE;
		}

		return 0;
	}
}