#include "Physics.h"
#include "GameEngine.h"
#include "Clock.h"
#include <iostream>

void Physics::Update()
{
	if (Clock::Get()->deltaTime != 0.0)
		gravity = -Clock::Get()->deltaTime * 4.8;
	
	for (int p = 0; p < physicsQue.size(); p++) {
		physicsQue[p]->x += physicsQue[p]->xSpeed;
		physicsQue[p]->z += physicsQue[p]->zSpeed;
		
		int test3 = ((int)(physicsQue[p]->z + 1.0)/ 64) * WORLD_SIZE + ((int)(physicsQue[p]->x + 1.0)/ 64);
		
		if (GameEngine::Get()->world.worldData[test3].blocks[(int)((physicsQue[p]->x + 1.0) - GameEngine::Get()->world.worldData[test3].x) / 2][(int)(physicsQue[p]->y) / 2][(int)((physicsQue[p]->z + 1.0) - GameEngine::Get()->world.worldData[test3].z) / 2].solid == true) {
			physicsQue[p]->x -= physicsQue[p]->xSpeed;
			physicsQue[p]->z -= physicsQue[p]->zSpeed;
		}
		physicsQue[p]->y += gravity;
		if (physicsQue[p]->y < 0 || GameEngine::Get()->world.worldData[test3].blocks[(int)((physicsQue[p]->x + 1.0) - GameEngine::Get()->world.worldData[test3].x) / 2][(int)(physicsQue[p]->y) / 2][(int)((physicsQue[p]->z + 1.0) - GameEngine::Get()->world.worldData[test3].z) / 2].solid == true) {
			physicsQue[p]->y -= gravity;
		}
		physicsQue[p]->y += physicsQue[p]->ySpeed;
		if (physicsQue[p]->ySpeed < 0 && GameEngine::Get()->world.worldData[test3].blocks[(int)((physicsQue[p]->x + 1.0) - GameEngine::Get()->world.worldData[test3].x) / 2][(int)(physicsQue[p]->y) / 2][(int)((physicsQue[p]->z + 1.0) - GameEngine::Get()->world.worldData[test3].z) / 2].solid == true) {
			physicsQue[p]->y -= physicsQue[p]->ySpeed;
		}
		else if (physicsQue[p]->ySpeed > 0 && GameEngine::Get()->world.worldData[test3].blocks[(int)((physicsQue[p]->x + 1.0) - GameEngine::Get()->world.worldData[test3].x) / 2][(int)(physicsQue[p]->y + 3.9) / 2][(int)((physicsQue[p]->z + 1.0) - GameEngine::Get()->world.worldData[test3].z) / 2].solid == true) {
			physicsQue[p]->y -= physicsQue[p]->ySpeed;
		}
		std::cout << Player::Get()->y << "\n";
	}
}
