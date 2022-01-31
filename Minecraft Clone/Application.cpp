#include "mcpch.h"
#include "Application.hpp"

Application::Application() 
	: m_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Clone", hv::Window::Style::Default)
{

}

Application::~Application() {

}

void Application::Update() {
	glfwPollEvents();
}

void Application::Render() {
	m_window.Clear();

	m_window.Display();
}

bool Application::IsOpen() const {
	return m_window.IsOpen();
}
