#include "World.h"
#include "RenderEngine.h"
#include "Player.h"
#include "ppm.h"
#include "PerlinNoise.h"
#include "ChunkManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Init chunks in world.
void World::Generate()
{
	//Perlin
	ppm image(3200, 3200);
	seed = 306;
	PerlinNoise pn(seed);
	double n;
	//
	for (int i = 0; i < WORLD_SIZE; i++) {
		for (int j = 0; j < WORLD_SIZE; j++) {
			
			Chunk chunk;
			chunk.Init(j * CHUNK_SIZE * 2, i * CHUNK_SIZE * 2);
			chunk.loaded = false;
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					n = pn.noise((double)(x + chunk.x / 2) / (double)22, (double)(z + chunk.z / 2) / (double)22, 0.8);
					//std::cout << n << "\n";
					n = floor(64 * n);
					//std::cout << n << "\n";
					//n += 1;
					n = n / (double)4.1 + (double)10;
					for (int y = 0; y < CHUNK_HEIGHT; y++) {
						if (y <= (int)n)
							chunk.blocks[x][y][z].solid = true;
						else
							chunk.blocks[x][y][z].solid = false;
					//
						if (y <= (int)n - 5)
							chunk.blocks[x][y][z].ID = STONE;
						else if (y <= (int)n - 1)
							chunk.blocks[x][y][z].ID = DIRT;
						else
							chunk.blocks[x][y][z].ID = GRASS;
						if (chunk.blocks[x][y][z].solid == false && y < 18) {
							chunk.blocks[x][y][z].solid = true;
							chunk.blocks[x][y][z].ID = WATER;
						}
						else if (chunk.blocks[x][y][z].solid == true && y == 17) {
							chunk.blocks[x][y][z].ID = SAND;
						}
						
					}
				}

			}
			chunk.LoadCache();
			worldData.push_back(chunk);
		}
	}
}

void World::OnExit()
{
	Save();
}

void World::Save()
{
	for (int i = 0; i < WORLD_SIZE; i++) {
		for (int j = 0; j < WORLD_SIZE; j++) {
			if(worldData[i * (int)WORLD_SIZE + j].changed == true)
				worldData[i * (int)WORLD_SIZE + j].CacheChunk();

		}
	}

}

void World::Update()
{

	glClearColor(0.50f, 0.64f, 1.0f, 1.0f);
	RemoveChunks();
	AddChunks();

	ChunkManager::Get()->ProcessLoadQue();
	for (int x = 0; x < ChunkManager::Get()->renderVector.size(); x++) {
		ChunkManager::Get()->renderVector[x]->Update();
	}

}

void World::RemoveChunks()
{
	for (int x = 0; x < ChunkManager::Get()->renderVector.size(); x++) {
		if (*&ChunkManager::Get()->renderVector[x]->x < (int)Player::Get()->x - 160 && ChunkManager::Get()->renderVector[x]->loaded == true) {
			ChunkManager::Get()->renderVector[x]->Unload();
			ChunkManager::Get()->renderVector.erase(ChunkManager::Get()->renderVector.begin() + x);
			ChunkManager::Get()->renderVector.shrink_to_fit();
			return;
		}
		
		if (*&ChunkManager::Get()->renderVector[x]->x > (int)Player::Get()->x + 160 && ChunkManager::Get()->renderVector[x]->loaded == true) {
			ChunkManager::Get()->renderVector[x]->Unload();
			ChunkManager::Get()->renderVector.erase(ChunkManager::Get()->renderVector.begin() + x);
			ChunkManager::Get()->renderVector.shrink_to_fit();
			return;
		}
		
		if (*&ChunkManager::Get()->renderVector[x]->z < (int)Player::Get()->z - 160 && ChunkManager::Get()->renderVector[x]->loaded == true) {
			ChunkManager::Get()->renderVector[x]->Unload();
			ChunkManager::Get()->renderVector.erase(ChunkManager::Get()->renderVector.begin() + x);
			ChunkManager::Get()->renderVector.shrink_to_fit();
			return;
		}
		
		if (*&ChunkManager::Get()->renderVector[x]->z > (int)Player::Get()->z + 160 && ChunkManager::Get()->renderVector[x]->loaded == true) {
			ChunkManager::Get()->renderVector[x]->Unload();
			ChunkManager::Get()->renderVector.erase(ChunkManager::Get()->renderVector.begin() + x);
			ChunkManager::Get()->renderVector.shrink_to_fit();
			return;
		}
	
	}
}

void World::AddChunks()
{
	for (int x = 0; x < worldData.size(); x++) {
		if (worldData[x].x > (int)Player::Get()->x - 160 && worldData[x].x < (int)Player::Get()->x + 160 && worldData[x].z >(int)Player::Get()->z - 160 && worldData[x].z < (int)Player::Get()->z + 160 && worldData[x].loaded != true) {
			if (worldData[x].loaded != true && worldData[x].inLoadQue != true) {
				if (worldData[x].x >= 64 && worldData[x].x < (WORLD_SIZE - 1) * 64 && worldData[x].z >= 64 && worldData[x].z < (WORLD_SIZE - 1) * 64 && worldData[x].peers[0] == nullptr) {
					worldData[x].peers[0] = &worldData[(worldData[x].z / 64 - 1) * WORLD_SIZE + (worldData[x].x / 64)];
					worldData[x].peers[1] = &worldData[(worldData[x].z / 64 + 1) * WORLD_SIZE + (worldData[x].x / 64)];
					worldData[x].peers[2] = &worldData[(worldData[x].z / 64) * WORLD_SIZE + (worldData[x].x / 64 - 1)];
					worldData[x].peers[3] = &worldData[(worldData[x].z / 64) * WORLD_SIZE + (worldData[x].x / 64 + 1)];
				}
				//worldData[x].Load();
			//	ChunkManager::Get()->renderVector.push_back(&worldData[x]);
				ChunkManager::Get()->AddToLoadQue(&worldData[x]);
				worldData[x].inLoadQue = true;
			}
		}

	}
}

void World::Render()
{
	for (int x = 0; x < ChunkManager::Get()->renderVector.size(); x++) {
		RenderEngine::Get()->Render(ChunkManager::Get()->renderVector[x]);
	}
}
