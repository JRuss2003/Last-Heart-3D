#pragma once
#include <chrono>
class Clock
{
public:
	void Tick();
	static Clock* Get() { static Clock clock; return &clock; }
	double TimeSinceLastAction();
	double deltaTime;
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point previousTime;
	std::chrono::steady_clock::time_point previousActionTime;
	std::chrono::steady_clock::time_point currentActionTime;
};

