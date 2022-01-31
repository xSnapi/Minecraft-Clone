#pragma once

#include "GLM/glm.hpp"

#include "Window.hpp"

namespace hv {
	enum class Button
	{
		Left = 0,
		Right,
		Middle,
		XButton1,
		XButton2,
	};

	class Mouse {
	public:
		static bool IsButtonPressed(Button button);

		static glm::vec2 GetPosition();
		static glm::vec2 GetPosition(const hv::Window& window);
	private:
		static void MouseCallback(GLFWwindow* window, double x, double y);

		static glm::vec2 s_pos;

		static bool s_locked;

		friend class Window;
	};
}