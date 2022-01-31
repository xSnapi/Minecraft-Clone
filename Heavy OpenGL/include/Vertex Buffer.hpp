#pragma once

namespace hv {
	class VertexBuffer {
	public:
		enum class Type 
		{
			Static = 0,
			Dynamic,
		};

		VertexBuffer(const void* data, uint32_t size, Type type = Type::Static);

		VertexBuffer();

		~VertexBuffer();

		uint8_t* Data(uint32_t offset = 0) const;
		void Allocate(const void* data, uint32_t size, Type type);
		void Reallocate(const void* data, uint32_t size, uint32_t offset, Type type);
		void Clear();

		void Bind() const;
		void Unbind() const;

		Type GetType() const;

	private:
		uint32_t m_id = 0;

		uint32_t m_size = 0;

		Type m_type = Type::Static;

		void Create(const void* data, uint32_t size);

		static int GetGLType(Type type);
	};
}