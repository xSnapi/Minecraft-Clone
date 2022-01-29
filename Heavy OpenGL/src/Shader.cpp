#include <hvpch.h>
#include "Shader.hpp"

namespace hv {
	Shader::Shader() {

	}

	Shader::~Shader() {
		if(m_id)
			glDeleteProgram(m_id);
	}

	void Shader::LoadFromFile(const std::string& vertex, const std::string& fragment) {
		std::string vertexSoruce   = Load(vertex);
		std::string fragmentSource = Load(fragment);

		if (vertexSoruce.empty() || fragmentSource.empty())
			return;

		Create(vertexSoruce, fragmentSource);
	}

	void Shader::LoadFromMemory(const std::string& vertex, const std::string& fragment) {
		Create(vertex, fragment);
	}

	void Shader::Bind() {
		glUseProgram(m_id);
	}

	void Shader::Unbind() {
		glUseProgram(0);
	}

	std::string Shader::Load(const std::string& path) {
		std::ifstream file(path);

		if (!file.good()) {
			hv::Debug::Log(hv::Color::Yellow, "[Failed to open file \"" + path, "\"]\n");
			return "";
		}

		std::string line;
		std::stringstream ss;

		while (std::getline(file, line))
			ss << line << '\n';

		file.close();
		
		return ss.str();
	}

	void Shader::Create(const std::string& vertex, const std::string& fragment) {
		m_id = glCreateProgram();

		uint32_t vertexShader   = CompileShader(GL_VERTEX_SHADER, vertex);
		uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment);

		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);

		glLinkProgram(m_id);
		glValidateProgram(m_id);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int res;
		glGetShaderiv(id, GL_COMPILE_STATUS, &res);

		if (res)
			return id;

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		
		#pragma warning(disable:6385)
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		#pragma warning(default:6385)

		Debug::Log(Color::Yellow, "[Failed to compile ", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), " shader!]\n");
		std::cout << message << std::endl;
		
		glDeleteShader(0);
		return 0;
	}
}
