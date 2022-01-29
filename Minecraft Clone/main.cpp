#include "mcpch.h"

int main() {
	hv::Window window;
	window.Create(800, 800, "Minecraft");

	while (window.IsOpen()) {
		window.Clear();
		window.Display();
		glfwPollEvents();
	}
}