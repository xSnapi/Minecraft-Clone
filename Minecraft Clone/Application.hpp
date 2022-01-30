#pragma once

class Application {
public:
	Application();
	~Application();

	void Run();

private:
	hv::Window m_window;

	hv::VertexBuffer	   buffer;
	hv::IndexBuffer		   indexBuffer;
	hv::VertexBufferLayout layout;

	hv::VertexArray  array;

	hv::Shader m_shader;

	glm::mat4 mat = glm::mat4(1.0f);

	void InitShaders();

	void Update();
	void Render();

	void HandleEvents();
};