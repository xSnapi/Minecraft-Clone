#pragma once

#include <cstdint>
#include "GLM/vec2.hpp"

namespace hv {
	class Texture {
	public:
		Texture();
		~Texture();

		void LoadFromFile(const std::string& path);

		void SetSmooth(bool smooth);

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;

		glm::vec2 GetSize() const;

	private:
		uint32_t m_id	  = 0;
		uint8_t* m_buffer = 0;

		int m_bitsPerPixel = 0;
		
		int m_width  = 0;
		int m_height = 0;

		void LoadSource(const std::string& path);
		void Create();
	};
}