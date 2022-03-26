#pragma once
#include "GL/glew.h"

class Textures
{
public:
	GLuint tileset;
	void Load();
	static Textures* Get() { static Textures textures; return &textures; }
};
