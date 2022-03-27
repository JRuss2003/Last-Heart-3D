#pragma once
#include <GL/glew.h>
#define GRASS 0
#define DIRT 1
#define BRICK 2
#define WOOD 3
#define STONE 4
#define WATER 5
#define SAND 6
#define CACTUS 7
#define LEAF 8
#define LOG 9

class Block
{
public:
	bool solid;
	short ID;
};

extern int blockVertexData[108];
extern GLfloat uv_buffer_data[72];

