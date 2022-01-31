#include <hvpch.h>
#include "Window.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3native.h>

#include "stb_image.hpp"

#include "Heavy Times.hpp"
#include "Mouse.hpp"

#include "Shape.hpp"

using namespace hv;

Window::Window(uint32_t width, uint32_t height, std::string title, Style style) {
	system("cls");

	Create(width, height, title, style);
}

Window::Window() {
	system("cls");
}

Window::~Window() {
	glfwTerminate();
}

void Window::Create(uint32_t width, uint32_t height, std::string title, Style style) {
	if (!InitGLFW())
		return;

	m_width  = width;
	m_height = height;

	m_title  = title;
	m_style  = style;

	if (!InitWindow()) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	if (!InitGLEW()) {
		glfwTerminate();
		return;
	}

	InitDefaultSettings();

	CenterWindow();
}

void Window::Display() { 
	glfwSwapBuffers(m_window);
	Times::DT = m_deltaClock.Restart();
}

void Window::Clear(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void hv::Window::CaptureMouse(bool var) {
	glfwSetInputMode(m_window, GLFW_CURSOR, var ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

	Mouse::s_locked = var;
}

void* hv::Window::GetHandle() const {
	return glfwGetWin32Window(m_window);
}

bool Window::IsOpen() const {
	return !glfwWindowShouldClose(m_window);
}

bool Window::InitGLEW() {
	glewExperimental = true;

	if (glewInit()) {
		hv::Debug::Log(hv::Color::Red, "[GLEW Initialization failed!]\n");
		return false;
	}

	return true;
}

bool Window::InitGLFW() {
	if (!glfwInit()) {
		hv::Debug::Log(hv::Color::Red, "[GLFW Initialization failed!]\n");
		return false;
	}

	return true;
}

bool Window::InitWindow() {
	if(m_style == Style::Default)
		glfwWindowHint(GLFW_RESIZABLE, false);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback([](int error, const char* msg) {
		std::string s("[" + std::to_string(error) + "] " + msg + '\n');
		std::cerr << s << std::endl;
		system("pause");
	});

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), false, false);

	if (!m_window) {
		hv::Debug::Log(hv::Color::Red, "[Window Initialization failed!]\n");
		return false;
	}

	return true;
}

void Window::CenterWindow() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowPos
	(
		m_window, 
		mode->width  / 2 - (int)m_width  / 2, 
		mode->height / 2 - (int)m_height / 2
	);
}

void Window::InitDefaultSettings() {
	{
		stbi_set_flip_vertically_on_load(true);
	}

	{
		glfwSetCursorPosCallback(m_window, Mouse::MouseCallback);
	}

	{
		glDepthFunc(GL_LESS);
	}

	{
		glm::mat4 projection = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height, -1000.0f, 1000.0f);
		Shape::Init(projection);
	}

	{
		RenderTarget::Init();
	}

	Debug::Log(Color::Green, "[Window initialized ", glGetString(GL_VERSION), "]");
}

