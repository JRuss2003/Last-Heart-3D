#pragma once
#include "Entity.h"
#include <vector>

class Physics
{
public:
	void Update();
	static Physics* Get() { static Physics physics; return &physics; }
	double gravity;
	std::vector<Entity*> physicsQue;
};

