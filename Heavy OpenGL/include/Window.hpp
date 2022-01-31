#pragma once

#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/vec4.hpp>

#include "Render Target.hpp"
#include "Clock.hpp"

namespace hv {
	class Window : public RenderTarget {
	public:
		enum class Style
		{
			Default = 0,
		};

		Window(uint32_t width, uint32_t height, std::string title, Style style);

		Window();

		~Window();

		void Create(uint32_t width, uint32_t height, std::string title, Style style = Style::Default);

		void Display();
		void Clear(glm::vec4 color = { });

		void CaptureMouse(bool var);

		void* GetHandle() const;

		bool IsOpen() const;
	private:
		GLFWwindow* m_window = nullptr;

		Clock m_deltaClock;

		uint32_t m_width  = 0;
		uint32_t m_height = 0;

		uint32_t m_frameLimit = 0;

		std::string m_title;

		Style m_style = Style::Default;

		bool InitGLEW();
		bool InitGLFW();
		bool InitWindow();

		void CenterWindow();

		void InitDefaultSettings();
	};
}