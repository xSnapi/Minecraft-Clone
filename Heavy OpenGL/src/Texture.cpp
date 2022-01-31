#include <hvpch.h>
#include "Texture.hpp"

#include "stb_image.hpp"

using namespace hv;

Texture::Texture() {
	
}

Texture::~Texture() {
	if (m_id)
		glDeleteTextures(1, &m_id);
}

void Texture::LoadFromFile(const std::string& path) {
	LoadSource(path);
	
	if (!m_buffer) {
		Debug::Log(Color::Yellow, "[Failed to load texture " + path + "]");
		return;
	}

	Create();
}

void Texture::SetSmooth(bool smooth) {
	if (smooth) {
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}

void Texture::Bind(uint32_t slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 Texture::GetSize() const {
	return glm::vec2(m_width, m_height);
}

void Texture::LoadSource(const std::string& path) {
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);
}

void Texture::Create() {
	glGenTextures(1, &m_id);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);

	if (m_buffer)
		stbi_image_free(m_buffer);
}
