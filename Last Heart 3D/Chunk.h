#pragma once
#include "glm/glm.hpp"
#include "Block.h"
#include <vector>
#define CHUNK_SIZE 32
#define CHUNK_HEIGHT 64

class Chunk
{
public:
	void Init(float x, float z);
	void Load();
	void Unload();
	void Update();
	void CacheChunk();
	void LoadCache();
	void FilterVisibleBlocks(int x, int y, int z);
	void FillVertexBuffer(int x, int y, int z);
	void FillUVBuffer(int x, int y, int z);
	Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
	std::vector<int> vertexData;
	std::vector<glm::vec2> uvData;
	std::vector<unsigned int> indices;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint elementbuffer;
	glm::mat4 model;
	glm::mat4 mvp;
	bool loaded;
	int x, z;
	bool init;
	GLuint VertexArrayID;
	Chunk* peers[4];
	bool changed;
};