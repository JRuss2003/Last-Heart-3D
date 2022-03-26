#include "Player.h"
#include <math.h>
#include "GameEngine.h"
#include "iostream"
#include "Clock.h"
void Player::MineBlock()
{
	if (Clock::Get()->TimeSinceLastAction() < 100000.0 || Clock::Get()->TimeSinceLastAction() != 0.0)
		return;
	targetX = this->x + 1;
	targetY = this->y + 1;
	targetZ = this->z + 1;
	hasHitTarget = false;
	for (int x = 0; x < 60; x++) {
		targetX += cos(angle) / 16.0;
		targetZ += sin(angle) / 16.0;
		targetY += tan(angleY) / 16.0;
		int test1 = ((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64);
		if (targetX > 64.0 && targetX < (WORLD_SIZE - 1) * 64 && targetY > 1 && targetY < CHUNK_HEIGHT * 2 && targetZ > 64.0 && targetZ < (WORLD_SIZE - 1) * 64) {
			if (GameEngine::Get()->world.worldData[test1].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid == true) {
				targetX -= cos(angle) / 12.0;
				targetZ -= sin(angle) / 12.0;
				targetY -= tan(angleY) / 12.0;
				while (GameEngine::Get()->world.worldData[test1].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid != true ) {
					targetX += cos(angle) / 80.0;
					targetZ += sin(angle) / 80.0;
					targetY += tan(angleY) / 80.0;
				}
				GameEngine::Get()->world.worldData[test1].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid = false;
				hasHitTarget = true;
			}

			if (GameEngine::Get()->world.worldData[((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64)].loaded == true) {
				GameEngine::Get()->world.worldData[((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64)].Unload();
				GameEngine::Get()->world.worldData[((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64)].Load();

			}


		}

		if (hasHitTarget)
			return;
	}
}

void Player::BuildBlock()
{
	if (Clock::Get()->TimeSinceLastAction() < 100000.0 || Clock::Get()->TimeSinceLastAction() != 0.0)
		return;
	targetX = this->x + 1;
	targetY = this->y + 1;
	targetZ = this->z + 1;
	hasHitTarget = false;
	for (int x = 0; x < 40; x++) {
			targetX += cos(angle) / 6.0;
			targetZ += sin(angle) / 6.0;
			targetY += tan(angleY) / 6.0;
			int test2 = ((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64);
		if (targetX > 1 && targetX < (WORLD_SIZE - 1) * 64 && targetY > 1 && targetY < CHUNK_HEIGHT * 2 && targetZ > 1 && targetZ < (WORLD_SIZE - 1) * 64) {
			if (GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].blocks[((int)targetX % 64) / 2][(int)targetY / 2][((int)targetZ % 64) / 2].solid == true) {
				while (GameEngine::Get()->world.worldData[test2].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid == true) {
					targetX -= cos(angle) / 80.0;
					targetZ -= sin(angle) / 80.0;
					targetY -= tan(angleY) / 80.0;
				}
				GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].blocks[((int)(targetX)% 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid = true;
				GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].ID = blockID;
				GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].changed = true;
				hasHitTarget = true;
			}

			if (GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].loaded == true) {
				GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].Unload();
				GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].Load();

			}


		}

		if (hasHitTarget)
			return;
	}
}
