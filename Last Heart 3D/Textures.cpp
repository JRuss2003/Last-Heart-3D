#include "Textures.h"
#include "RenderEngine.h"

void Textures::Load()
{
	tileset = RenderEngine::Get()->LoadTexture("GameData/Textures/tileset.bmp");
}
