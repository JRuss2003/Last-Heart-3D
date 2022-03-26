#pragma once
#include <GL/glew.h>
#include "Camera.h"
#include "Chunk.h"

class RenderEngine
{
public:
	void Init();
	void BindTexture(GLuint* targetTexture);
	void Render(Chunk* chunk);
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	GLuint LoadTexture(const char* filename);
	static RenderEngine* Get() { static RenderEngine renderEngine; return &renderEngine; }
	GLuint ProgramID;
	unsigned char* data;
};
