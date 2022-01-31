#include "mcpch.h"

#include "Application.hpp"

int main() {
	Application application;

	while (application.s_window.IsOpen()) {
		application.Update();
		application.Render();
	}

	return EXIT_SUCCESS;
}