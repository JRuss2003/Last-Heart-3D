#include "Chunk.h"
#include "Camera.h"
#include "GameEngine.h"
#include "iostream"
#include <fstream>
#include <sstream>

void Chunk::Init(float x, float z)
{
	loaded = true;
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0.0f, z));
	this->x = x;
	this->z = z;
}

void Chunk::Load()
{
	loaded = true;
	//Fill vertex vector
	for (int z = 0; z < CHUNK_SIZE; z++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				if (blocks[x][y][z].solid == true)
				{
					FilterVisibleBlocks(x, y, z);
				}
			}
		}
	}
	//fill index buffer

	for (int x = 0; x < vertexData.size(); x++) {
		if (x % 3 == 0) {
			indices.push_back(x / 3);
		}
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//Load vertex data
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(unsigned int), &vertexData[0], GL_STATIC_DRAW);

	//Load uv data
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(glm::vec2), &uvData[0], GL_STATIC_DRAW);

	//Load index data
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

}

void Chunk::Unload()
{
	//Free buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	//Free vectors, since clearing them doesnt free the memory apparently :s
	loaded = false;
	vertexData.clear();
	vertexData.shrink_to_fit();
	uvData.clear();
	uvData.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
}

void Chunk::Update()
{
	mvp = Camera::Get()->projection * Camera::Get()->view * model;
}

void Chunk::CacheChunk()
{
	std::string cachePath;
	cachePath += "saves/";
	cachePath += std::to_string(x);
	cachePath += std::to_string(z);
	cachePath += ".txt";
	std::ofstream chunk_fs(cachePath, std::ios::out);
	if (chunk_fs.is_open()) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					if (blocks[x][y][z].solid == true) {
						chunk_fs.write("1", 1);
					}
					else {

						chunk_fs.write("0", 1);
					}

				}
			}
		}
		//
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					std::string tempString = std::to_string(blocks[x][y][z].ID);
					chunk_fs.write(tempString.c_str(), 1);

				}
			}
		}

	}
	chunk_fs.close();
}

void Chunk::LoadCache()
{
	std::stringstream sstr;

	std::string cachePath;
	cachePath += "saves/";
	cachePath += std::to_string(x);
	cachePath += std::to_string(z);
	cachePath += ".txt";
	sstr.clear();
	std::ifstream chunkfile(cachePath, std::ios::in);
	sstr << chunkfile.rdbuf();
	cachePath = sstr.str();
	if (chunkfile.is_open()) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					if (cachePath[x + (int)CHUNK_SIZE * y + (int)CHUNK_SIZE * (int)CHUNK_HEIGHT * z] == '1')
						blocks[x][y][z].solid = true;
					else
						blocks[x][y][z].solid = false;
					//
					std::string tempS;
					tempS = cachePath[65536 + (x + (int)CHUNK_SIZE * y + (int)CHUNK_SIZE * (int)CHUNK_HEIGHT * z)];
					blocks[x][y][z].ID = std::stoi(tempS);
				}
			}
		}

	}
	chunkfile.close();
}

void Chunk::FilterVisibleBlocks(int x, int y, int z)
{
	//Filter blocks, a peer is a neighbor chunk pointer that is used to compare neighbor blocks outside of the chunk's bounds.
	if (x > 0 && x < CHUNK_SIZE - 1 && z > 0 && z < CHUNK_SIZE - 1 && y > 0 && y < CHUNK_HEIGHT - 1) {
		if (this->blocks[x - 1][y][z].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
		}
		return;
	}
	
	if (y == CHUNK_HEIGHT - 1) {
		FillVertexBuffer(x, y, z);
		FillUVBuffer(x, y, z);
		return;
	}
	
	
	if (y == 0) {
		if (blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			
		}
		return;
	}
	
	if (x == 0 && z == 0) {
		if (peers[0] == nullptr) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[2]->blocks[x + CHUNK_SIZE - 1][y][z].solid != true || peers[0]->blocks[x][y][z + CHUNK_SIZE - 1].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	if (x == 0 && z == CHUNK_SIZE - 1) {
		if (peers[0] == nullptr) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[2]->blocks[x + CHUNK_SIZE - 1][y][z].solid != true || peers[1]->blocks[x][y][z - CHUNK_SIZE + 1].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	if (x == CHUNK_SIZE - 1 && z == 0) {
		if (peers[0] == nullptr) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[3]->blocks[x - CHUNK_SIZE + 1][y][z].solid != true || peers[0]->blocks[x][y][z + CHUNK_SIZE - 1].solid != true || this->blocks[x - 1][y][z].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	if (x == CHUNK_SIZE - 1 && z == CHUNK_SIZE - 1) {
		if (peers[0] == nullptr) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[3]->blocks[x - CHUNK_SIZE + 1][y][z].solid != true || peers[1]->blocks[x][y][z - CHUNK_SIZE + 1].solid != true || this->blocks[x - 1][y][z].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	
	if (x == 0) {
		if (this->peers[0] == nullptr){
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		if (peers[2]->blocks[x + CHUNK_SIZE - 1][y][z].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	if (x == CHUNK_SIZE - 1) {
		if (peers[0] == nullptr){
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[3]->blocks[x - CHUNK_SIZE + 1][y][z].solid != true || this->blocks[x - 1][y][z].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	if (z == 0) {
		if (peers[0] == nullptr){
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[0]->blocks[x][y][z + CHUNK_SIZE - 1].solid != true || this->blocks[x][y][z + 1].solid != true || this->blocks[x - 1][y][z].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	
	if (z == CHUNK_SIZE - 1) {
		if (peers[0] == nullptr){
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		else if (peers[1]->blocks[x][y][z - CHUNK_SIZE + 1].solid != true || this->blocks[x][y][z - 1].solid != true || this->blocks[x - 1][y][z].solid != true || this->blocks[x + 1][y][z].solid != true || this->blocks[x][y - 1][z].solid != true || this->blocks[x][y + 1][z].solid != true) {
			FillVertexBuffer(x, y, z);
			FillUVBuffer(x, y, z);
			return;
		}
		return;
	}
	
	
}

void Chunk::FillVertexBuffer(int x, int y, int z)
{
	for (int c = 0; c < 108; c++) {
		if (c % 3 == 0) {
			this->vertexData.push_back((int)blockVertexData[c] + x * 2);
			this->vertexData.push_back((int)blockVertexData[c + 1] + y * 2);
			this->vertexData.push_back((int)blockVertexData[c + 2] + z * 2);
		}
	}
	
}

void Chunk::FillUVBuffer(int x, int y, int z)
{
	
	//Fill uv buffer with correct texture coodinates for block ID.
	switch (this->blocks[x][y][z].ID) {
	case GRASS:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0) + (0.125 * 1.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 7.0)));
		}
		return;
	case DIRT:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0) + (0.125 * 1.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 6.0)));
		}
		return;
	case BRICK:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 7.0)));
		}
		return;
	case STONE:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 6.0)));
		}
		return;
	case WOOD:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0) + (0.125 * 2.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 7.0)));
		}
		return;
	default:
		for (int c = 0; c < 72; c++) {
			if (c % 2 == 0)
				this->uvData.push_back(glm::vec2((uv_buffer_data[c] / 8.0), (uv_buffer_data[c + 1] / 8.0) + (0.125 * 7.0)));
		}
		return;
	}
}

