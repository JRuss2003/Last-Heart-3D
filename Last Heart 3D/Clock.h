#pragma once
#include <chrono>
class Clock
{
public:
	void Tick();
	static Clock* Get() { static Clock clock; return &clock; }
	double deltaTime;
	std::chrono::steady_clock::time_point previousTime;
};

