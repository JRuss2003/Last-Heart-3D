#pragma once
#include <GL/glew.h>
#define GRASS 0
#define DIRT 1
#define BRICK 2
#define WOOD 3
#define STONE 4

class Block
{
public:
	bool solid;
	short ID;
};

extern int blockVertexData[108];
extern GLfloat uv_buffer_data[72];

