#include "World.h"
#include "RenderEngine.h"
#include "Player.h"
#include "ppm.h"
#include "PerlinNoise.h"
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
			chunk.x = j * CHUNK_SIZE * 2;
			chunk.z = i * CHUNK_SIZE * 2;
			chunk.init = false;
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
	//Remove chunks if they are out of range
	RemoveChunks();
	//If in world bounds, add chunks in range
	if (Player::Get()->z >= 0 && Player::Get()->z < WORLD_SIZE * 64 && Player::Get()->x >= 0 && Player::Get()->x < WORLD_SIZE * 64)
	{
		//Init chunk if not done already.
		if (worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].init != true) {
			//If chunk is not an edge, add peer chunks (next to target chunk)
			if (Player::Get()->z >= 64.0f && Player::Get()->z < (WORLD_SIZE - 1) * 64.0f && Player::Get()->x >= 64 && Player::Get()->x < (WORLD_SIZE - 1) * 64.0f) {
				worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].peers[0] = &worldData[((int)Player::Get()->z / 64 - 1) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)];
				worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].peers[1] = &worldData[((int)Player::Get()->z / 64 + 1) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)];
				worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].peers[2] = &worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64 - 1)];
				worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].peers[3] = &worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64 + 1)];
			}
			worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].Init((int)Player::Get()->x / 64 * 64, (int)Player::Get()->z / 64 * 64);
			renderVector.push_back(&worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)]);
			
		}
		//Load if unloaded and in range
		else if(worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].loaded != true) {
			worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)].Load();
			renderVector.push_back(&worldData[((int)Player::Get()->z / 64) * (int)WORLD_SIZE + ((int)Player::Get()->x / 64)]);

		}
		
	}
	AddChunks();

	//Update the projection of each visible chunk.
	for (int x = 0; x < renderVector.size(); x++) {
		renderVector[x]->Update();
	}
	
}

void World::RemoveChunks()
{
	for (int x = 0; x < renderVector.size(); x++) {
		if (*&renderVector[x]->x < (int)Player::Get()->x - 192) {
			this->renderVector[x]->Unload();
			this->renderVector.erase(renderVector.begin() + x);
			renderVector.shrink_to_fit();
			return;
		}
		
		if (*&renderVector[x]->x > (int)Player::Get()->x + 192) {
			this->renderVector[x]->Unload();
			this->renderVector.erase(renderVector.begin() + x);
			renderVector.shrink_to_fit();
			return;
		}
		
		if (*&renderVector[x]->z < (int)Player::Get()->z - 192) {
			renderVector[x]->Unload();
			renderVector.erase(renderVector.begin() + x);
			renderVector.shrink_to_fit();
			return;
		}
		
		if (*&renderVector[x]->z > (int)Player::Get()->z + 192) {
			renderVector[x]->Unload();
			renderVector.erase(renderVector.begin() + x);
			renderVector.shrink_to_fit();
			return;
		}
	
	}
}

void World::AddChunks()
{
	for (int x = 0; x < worldData.size(); x++) {
		if (worldData[x].x > (int)Player::Get()->x - 192 && worldData[x].x < (int)Player::Get()->x + 192 && worldData[x].z >(int)Player::Get()->z - 192 && worldData[x].z < (int)Player::Get()->z + 192 && worldData[x].loaded != true) {
			if (worldData[x].init == true) {
				worldData[x].Load();
			}
			else {
				if (worldData[x].x >= 64 && worldData[x].x < (WORLD_SIZE - 1) * 64 && worldData[x].z >= 64 && worldData[x].z < (WORLD_SIZE - 1) * 64) {
					worldData[x].peers[0] = &worldData[(worldData[x].z / 64 - 1) * WORLD_SIZE + (worldData[x].x / 64)];
					worldData[x].peers[1] = &worldData[(worldData[x].z / 64 + 1) * WORLD_SIZE + (worldData[x].x / 64)];
					worldData[x].peers[2] = &worldData[(worldData[x].z / 64) * WORLD_SIZE + (worldData[x].x / 64 - 1)];
					worldData[x].peers[3] = &worldData[(worldData[x].z / 64) * WORLD_SIZE + (worldData[x].x / 64 + 1)];
				}
				worldData[x].Init(worldData[x].x, worldData[x].z);
			}
			renderVector.push_back(&worldData[x]);
			return;
		}

	}
}

void World::Render()
{
	for (int x = 0; x < renderVector.size(); x++) {
		RenderEngine::Get()->Render(renderVector[x]);
	}
}
