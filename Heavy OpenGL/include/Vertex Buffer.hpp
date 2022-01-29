#pragma once

namespace hv {
	class VertexBuffer {
	public:
		enum class Type 
		{
			Draw = 0,
		};

		VertexBuffer(const void* data, uint32_t size, Type type = Type::Draw);

		VertexBuffer();

		~VertexBuffer();

		void Append(const void* data, uint32_t size, Type type);

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_id = 0;
		
		Type m_type = Type::Draw;

		void Create(const void* data, uint32_t size);

		static int GetGLType(Type type);
	};
}