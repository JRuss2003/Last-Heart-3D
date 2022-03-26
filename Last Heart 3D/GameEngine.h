#pragma once
#include "Window.h"
#include "EventProcessor.h"
#include "RenderEngine.h"
#include "Chunk.h"
#include "Textures.h"
#include "World.h"
#include "Clock.h"
class GameEngine
{
public:
	void Init(int x, int y, int width, int height);
	void Update();
	static GameEngine* Get() { static GameEngine gameEngine; return &gameEngine; }
	bool isRunning;
	World world;
	GLuint Texture;
};
