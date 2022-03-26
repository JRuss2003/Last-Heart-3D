#include "Clock.h"
void Clock::Tick()
{
	now = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - previousTime).count() / 100000.0f;
	previousTime = now;
}

double Clock::TimeSinceLastAction()
{
	currentActionTime = std::chrono::steady_clock::now();
	double timeSince = std::chrono::duration_cast<std::chrono::microseconds>(currentActionTime - previousActionTime).count();
	previousActionTime = currentActionTime;
	return timeSince;
}
