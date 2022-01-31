#include <hvpch.h>
#include "Mouse.hpp"

#include <Windows.h>

using namespace hv;

glm::vec2	Mouse::s_pos;
bool		Mouse::s_locked = false;

bool hv::Mouse::IsButtonPressed(Button button) {
	int vkey = 0;
	switch (button)
	{
		case Button::Left:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
		case Button::Right:    vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
		case Button::Middle:   vkey = VK_MBUTTON;  break;
		case Button::XButton1: vkey = VK_XBUTTON1; break;
		case Button::XButton2: vkey = VK_XBUTTON2; break;
		default:               vkey = 0;           break;
	}

	return (GetAsyncKeyState(vkey) & 0x8000) != 0;
}

glm::vec2 Mouse::GetPosition() {
	if (s_locked)
		return s_pos;

	POINT point;
	GetCursorPos(&point);
	return glm::vec2(point.x, point.y);
}

glm::vec2 Mouse::GetPosition(const hv::Window& window) {
	if (s_locked)
		return s_pos;

	HWND__* handle = (HWND__*)window.GetHandle();
	if (handle)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(handle, &point);
		return glm::vec2(point.x, point.y);
	}
	else
	{
		return glm::vec2(0.0f, 0.0f);
	}
}

void Mouse::MouseCallback(GLFWwindow* window, double x, double y) {
	s_pos.x = x;
	s_pos.y = y;
}
