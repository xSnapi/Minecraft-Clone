#pragma once

#include <iostream>

namespace hv {
	enum class Color
	{
		Red = 0,
		Green,
		Yellow,
		Blue,
	};

	class Debug {
	public:
		// Color log function
		template<typename ...Args>
		constexpr static void Log(Color color, Args&&... args) {
			std::cout << ColorAnsi(color);
			(std::cerr << ... << args);
			std::cout << "\033[0m";
		}

		template<typename ...Args>
		constexpr static void Log(Args&&... args) {
			(std::cerr << ... << args);
		}

	private:
		static const char* ColorAnsi(Color color) {
			switch (color) {
			case Color::Red:
				return "\x1B[31m";
			case Color::Green:
				return "\x1B[32m";
			case Color::Yellow:
				return "\x1B[33m";
			case Color::Blue:
				return "\x1B[34m";
			}

			return "";
		}
	};
}