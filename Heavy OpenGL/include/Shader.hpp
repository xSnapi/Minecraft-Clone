#pragma once

#include <string>

namespace hv {
	class Shader {
	public:
		Shader();

		~Shader();

		void LoadFromFile(const std::string& vertex, const std::string& fragment);
		void LoadFromMemory(const std::string& vertex, const std::string& fragment);

		void Bind();
		void Unbind();

	private:
		uint32_t m_id = 0;

		std::string Load(const std::string& path);

		void Create(const std::string& vertex, const std::string& fragment);

		uint32_t CompileShader(uint32_t type, const std::string& source);
	};
}