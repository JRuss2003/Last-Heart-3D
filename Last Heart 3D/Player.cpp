#include "Player.h"
#include <math.h>
#include "GameEngine.h"
#include "iostream"
#include "Clock.h"
void Player::MineBlock()
{
	targetX = this->x + 1;
	targetY = this->y + 1;
	targetZ = this->z + 1;
	hasHitTarget = false;
	for (int x = 0; x < 100; x++) {
		targetX += cos(angle) / 16.0;
		targetZ += sin(angle) / 16.0;
		targetY += tan(angleY) / 16.0;
		int test1 = ((int)targetZ / 64) * WORLD_SIZE + ((int)targetX / 64);
		if (targetX > 64.0 && targetX < (WORLD_SIZE - 1) * 64 && targetY > 1 && targetY < CHUNK_HEIGHT * 2 && targetZ > 64.0 && targetZ < (WORLD_SIZE - 1) * 64) {
			if (GameEngine::Get()->world.worldData[test1].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid == true) {
				targetX -= cos(angle) / 16.0;
				targetZ -= sin(angle) / 16.0;
				targetY -= tan(angleY) / 16.0;
				while (GameEngine::Get()->world.worldData[test1].blocks[((int)(targetX) % 64) / 2][(int)(targetY) / 2][((int)(targetZ) % 64) / 2].solid != true ) {
					targetX += cos(angle) / 400.0;
					targetZ += sin(angle) / 400.0;
					targetY += tan(angleY) / 400.0;
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
	targetX = this->x + 1;
	targetY = this->y + 1;
	targetZ = this->z + 1;
	hasHitTarget = false;
	for (int x = 0; x < 40; x++) {
			targetX += cos(angle);
			targetZ += sin(angle);
			targetY += tan(angleY);

		if (targetX > 1 && targetX < (WORLD_SIZE - 1) * 64 && targetY > 1 && targetY < CHUNK_HEIGHT * 2 && targetZ > 1 && targetZ < (WORLD_SIZE - 1) * 64) {
			if (GameEngine::Get()->world.worldData[((int)(targetZ) / 64) * WORLD_SIZE + ((int)(targetX) / 64)].blocks[((int)targetX % 64) / 2][(int)targetY / 2][((int)targetZ % 64) / 2].solid == true) {
				GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX -cos(angle)) / 64)].blocks[((int)(targetX - cos(angle))% 64) / 2][(int)(targetY - tan(angleY)) / 2][((int)(targetZ - sin(angle)) % 64) / 2].solid = true;
				GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX - cos(angle)) / 64)].blocks[((int)(targetX - cos(angle)) % 64) / 2][(int)(targetY - tan(angleY)) / 2][((int)(targetZ - sin(angle)) % 64) / 2].ID = blockID;
				GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX - cos(angle)) / 64)].changed = true;
				hasHitTarget = true;
			}

			if (GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX - cos(angle)) / 64)].loaded == true) {
				GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX - cos(angle)) / 64)].Unload();
				GameEngine::Get()->world.worldData[((int)(targetZ - sin(angle)) / 64) * WORLD_SIZE + ((int)(targetX - cos(angle)) / 64)].Load();

			}


		}

		if (hasHitTarget)
			return;
	}
}
