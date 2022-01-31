#pragma once

#include <string>
#include <unordered_map>

#include "GLM/glm.hpp"

namespace hv {
	class Shader {
	public:
		Shader();

		~Shader();

		void LoadFromFile(const std::string& vertex, const std::string& fragment);
		void LoadFromMemory(const std::string& vertex, const std::string& fragment);

		void Bind() const;
		void Unbind() const;

		// Uniforms
		void SetUniformFloat(const std::string& name, float value);

		void SetUniformVec2(const std::string& name, glm::vec2 vec);

		void SetUniformVec3(const std::string& name, glm::vec3 vec);

		void SetUniformVec4(const std::string& name, glm::vec4 vec);

		void SetUniformMat4(const std::string& name, const glm::mat4& mat, uint32_t count = 1);

	private:
		uint32_t m_id = 0;

		std::unordered_map<std::string, int> m_uniformCache;

		std::string Load(const std::string& path);

		void Create(const std::string& vertex, const std::string& fragment);

		uint32_t CompileShader(uint32_t type, const std::string& source);

		int GetUniformLocation(const std::string& name);
	};
}