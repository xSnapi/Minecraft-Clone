#include <hvpch.h>
#include "Shader.hpp"

using namespace hv;

Shader::Shader() {

}

Shader::~Shader() {
	if(m_id)
		glDeleteProgram(m_id);
}

void Shader::LoadFromFile(const std::string& vertex, const std::string& fragment) {
	std::string vertexSoruce   = Load(vertex);
	std::string fragmentSource = Load(fragment);

	if (vertexSoruce.empty() || fragmentSource.empty()) {
		Debug::Log(Color::Yellow, "[Vertex or fragment shader was empty]\n");
		return;
	}

	Create(vertexSoruce, fragmentSource);
}

void Shader::LoadFromMemory(const std::string& vertex, const std::string& fragment) {
	if (vertex.empty() || fragment.empty()) {
		Debug::Log(Color::Yellow, "[Vertex or fragment shader was empty]\n");
		return;
	}

	Create(vertex, fragment);
}

void Shader::Bind() const {
	glUseProgram(m_id);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniformFloat(const std::string& name, float value) {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformVec2(const std::string& name, glm::vec2 vec) {
	glUniform2f(GetUniformLocation(name), vec.x, vec.y);
}

void Shader::SetUniformVec3(const std::string& name, glm::vec3 vec) {
	glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const std::string& name, glm::vec4 vec) {
	glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat, uint32_t count) {
	glUniformMatrix4fv(GetUniformLocation(name), count, false, &mat[0][0]);
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

int Shader::GetUniformLocation(const std::string& name) {
	Bind();

	if (m_uniformCache.find(name) != m_uniformCache.end())
		return m_uniformCache[name];

	int location = glGetUniformLocation(m_id, name.c_str());

	if (location == -1) {
		Debug::Log(Color::Yellow, "[No active uniform with name \"" + name + "\" found]\n");
		return location;
	}

	m_uniformCache[name] = location;

	return location;
}

