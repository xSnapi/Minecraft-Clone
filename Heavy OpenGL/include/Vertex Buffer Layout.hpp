#pragma once

#include <vector>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace hv {
	enum class ElementType 
	{
		Float = 0,
		UInt32,
		UInt8,
	};

	class VertexBufferLayout {
	public:
		struct Element
		{
			Element(ElementType type, uint32_t size, uint8_t normalized);

			ElementType Type;

			uint32_t Size		= 0;
			uint8_t	 Normalized = 0;

			static uint32_t GetTypeSize(ElementType type);
			static uint32_t GetGLType(ElementType type);
		};

		VertexBufferLayout();

		~VertexBufferLayout();

		void Add(ElementType type, uint32_t size, uint8_t normalized = 0);

		uint32_t GetStride() const;
		const std::vector<Element>& GetElements() const;

	private:
		std::vector<Element> m_Elements;

		uint32_t m_stride = 0;

		void Push(ElementType type, uint32_t size, uint8_t normalized);
	};
}