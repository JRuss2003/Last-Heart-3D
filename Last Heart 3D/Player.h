#pragma once
class Player
{
public:
	void MineBlock();
	void BuildBlock();
	double x, y, z;
	double targetX, targetY, targetZ;
	double angle, angleY;
	static Player* Get() { static Player player; return &player; }
	bool hasHitTarget;
	short blockID;
};

