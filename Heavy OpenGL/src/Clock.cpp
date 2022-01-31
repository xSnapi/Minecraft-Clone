#include <hvpch.h>
#include "Clock.hpp"

using namespace hv;

Clock::Clock() 
	: m_now(clock::now())
{

}

Clock::~Clock() {

}

float Clock::GetElapsedTime() {
	return DurationToTime(clock::now() - m_now);
}

float Clock::Restart() {
	clock::time_point now = clock::now();

	float time = (DurationToTime(now - m_now));
	m_now = now;

	return time;
}

float Clock::DurationToTime(clock::duration duration) {
	return std::chrono::duration_cast<std::chrono::microseconds>(duration).count() * 0.000001f;
}
