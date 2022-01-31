#pragma once

#include <chrono>

namespace hv {
	class Clock {
	public:
		Clock();
		~Clock();

		float GetElapsedTime();
		float Restart();

	private:
		using clock = std::chrono::high_resolution_clock;

		static float DurationToTime(clock::duration duration);

		clock m_clock;
		clock::time_point  m_now;
	};
}