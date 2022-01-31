#pragma once

namespace hv {
	class IndexBuffer {
	public:
		IndexBuffer(const void* data, uint32_t bytes);

		IndexBuffer();

		~IndexBuffer();

		uint8_t* Data(uint32_t offset = 0) const;
		void Allocate(const void* data, uint32_t bytes);
		void Reallocate(const void* data, uint32_t bytes, uint32_t offset);
		void Clear();

		void Bind() const;
		void Unbind() const;

		uint32_t Size() const;

	private:

		uint32_t m_id	= 0;
		uint32_t m_size = 0;

		void Create(const void* data);
	};
}