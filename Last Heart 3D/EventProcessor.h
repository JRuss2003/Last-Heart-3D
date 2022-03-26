#pragma once

class EventProcessor
{
public:
	void PollEvents();
	static EventProcessor* Get() { static EventProcessor eventProcessor; return &eventProcessor; }
	double xpos, ypos;
};