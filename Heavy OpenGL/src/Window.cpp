#include <hvpch.h>
#include "Window.hpp"

#include "stb_image.hpp"

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
}

void Window::Display() { 
	glfwSwapBuffers(m_window);
}

void Window::Clear(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Window::InitDefaultSettings() {
	stbi_set_flip_vertically_on_load(true);

	RenderTarget::Init();

	std::cout << glGetString(GL_VERSION) << '\n';

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

