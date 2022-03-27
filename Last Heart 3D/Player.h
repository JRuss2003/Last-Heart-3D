#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	void MineBlock();
	void BuildBlock();
	double targetX, targetY, targetZ;
	static Player* Get() { static Player player; return &player; }
	bool hasHitTarget;
	short blockID;
};

