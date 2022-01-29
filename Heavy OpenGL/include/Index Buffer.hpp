#pragma once

namespace hv {
	class IndexBuffer {
	public:
		IndexBuffer(const void* data, uint32_t bytes);

		IndexBuffer();

		~IndexBuffer();

		void Append(const void* data, uint32_t bytes);

		void Bind() const;
		void Unbind() const;

		uint32_t Size() const;

	private:

		uint32_t m_id	= 0;
		uint32_t m_size = 0;

		void Create(const void* data);
	};
}