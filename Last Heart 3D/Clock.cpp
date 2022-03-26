#include "Clock.h"
#include <iostream>
void Clock::Tick()
{
	auto now = std::chrono::steady_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - previousTime).count() / 100000.0f;
	

	double frame = 60000000.00 / (now - previousTime).count();
	previousTime = now;
	//std::cout << frame << "\n";
}
