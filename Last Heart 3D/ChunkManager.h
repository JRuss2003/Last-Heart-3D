#pragma once
#include "Chunk.h"
#include <vector>

class ChunkManager
{
public:
	void ProcessUnloadQue();
	void ProcessLoadQue();
	void AddToUnloadQue(Chunk* targetChunk);
	void AddToLoadQue(Chunk* targetChunk);
	static ChunkManager* Get() { static ChunkManager chunkManager; return &chunkManager; }
	std::vector<Chunk*> loadQue;
	std::vector<Chunk*> unloadQue;
	std::vector<Chunk*> renderVector;
};

