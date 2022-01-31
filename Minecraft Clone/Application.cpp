#include "mcpch.h"
#include "Application.hpp"

#include "Game.hpp"

hv::Window Application::s_window;

Application::Application()  {
	s_window.Create(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Minecraft Clone", hv::Window::Style::Default);

	m_game = new Game();
}

Application::~Application() {

}

void Application::Update() {
	glfwPollEvents();

	m_game->Update();
}

void Application::Render() {
	s_window.Clear(hv::RGBToNVec4(glm::vec4(55.0f, 134.0f, 184.0f, 255.0f)));

	m_game->Render();

	s_window.Display();
}