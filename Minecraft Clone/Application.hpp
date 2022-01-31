#pragma once

#include "mcpch.h"

class Game;

class Application {
public:
	Application();
	~Application();

	void Update();
	void Render();

	static hv::Window s_window;

private:
	Game* m_game = nullptr;
};