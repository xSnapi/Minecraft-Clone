#include "mcpch.h"
#include "Application.hpp"

Application::Application() 
	: m_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Clone", hv::Window::Style::Default)
{
	InitShaders();

	hv::Vertex3D vertices[8] =
	{
		{ glm::vec3(-0.0f, -0.0f, -0.0f), glm::vec4(0.1f, 0.2f, 0.8f, 1.0f) },
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(0.1f, 0.2f, 0.8f, 1.0f) },
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(0.1f, 0.2f, 0.8f, 1.0f) },
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.1f, 0.2f, 0.8f, 1.0f) },

		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f) }
	};

	uint32_t indices[36] =
	{
		// Front
		0, 1, 2,
		2, 3, 0,

		// Back
		4, 5, 6,
		6, 7, 4,

		// Top
		3, 2, 6,
		6, 7, 3,


		// Bottom
		0, 1, 5,
		5, 4, 0,

		// Left
		4, 0, 3,
		3, 7, 4,

		// Right
		5, 1, 2,
		2, 6, 5
	};

	buffer.Append(vertices, 8 * sizeof(hv::Vertex3D), hv::VertexBuffer::Type::Draw);

	hv::Vertex3D* p = (hv::Vertex3D*)buffer.Data();

	p[0] = { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.1f, 0.2f, 0.8f, 1.0f) };

	indexBuffer.Append(indices, 36);

	layout.Add(hv::ElementType::Float, 3);
	layout.Add(hv::ElementType::Float, 2);
	layout.Add(hv::ElementType::Float, 4);

	array.AppendBuffer(buffer, layout, &indexBuffer);

	m_camera.Create(m_window, WINDOW_WIDTH, WINDOW_HEIGHT);

	m_camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	m_window.CaptureMouse(true);

	m_square.SetSize(glm::vec2(50.0f, 50.0f));
	m_circle.SetRadius(25.0f);
	m_circle.SetPosition(glm::vec2(1600.0f, 900.0f) / 2.0f);
	//m_square.SetOrigin(glm::vec2(50.0f, 50.0f) / 2.0f);
	//m_square.SetPosition(glm::vec2(1600.0f, 900.0f) / 2.0f);
}

Application::~Application() {

}

void Application::Run() {
	while (m_window.IsOpen()) {
		Update();
		Render();
	}
}

void Application::InitShaders() {
	{
		m_shader.LoadFromFile("res/shaders/default.vert", "res/shaders/default.frag");
	}
}

void Application::Update() {
	HandleEvents();

	glm::mat4 proj = m_camera.Update();

	static glm::mat4 trans(1.0f);

	trans = glm::rotate(trans, glm::radians(0.5f), glm::vec3(1.0f, 1.0f, 0.0f));

	//m_square.SetRotation(m_square.GetRotation() + 0.0005f);

	m_shader.SetUniformMat4("u_transform", trans);
	m_shader.SetUniformMat4("u_projection", proj);

	m_camera.BasicMove(4.0f);
	//m_square.SetRotation(m_square.GetRotation() + 0.5f);
}

void Application::Render() {
	m_window.Clear();

	m_window.Draw(array, hv::Primitives::Triangles, &m_shader);
	m_window.Draw(m_square);
	m_window.Draw(m_circle);
	
	m_window.Display();
}

void Application::HandleEvents() {
	glfwPollEvents();
}
