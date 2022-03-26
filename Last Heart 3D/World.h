#pragma once
#include "Chunk.h"
#include <vector>
#define WORLD_SIZE 60

class World
{
public:
	void Generate();
	void OnExit();
	void Save();
	void Update();
	void RemoveChunks();
	void AddChunks();
	void Render();
	std::vector<Chunk> worldData;
	unsigned int seed;
	
};

