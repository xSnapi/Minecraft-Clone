#pragma once

#include "mcpch.h"

class Application {
public:
	Application();
	~Application();

	void Update();
	void Render();

	bool IsOpen() const;
private:
	hv::Window m_window;
};