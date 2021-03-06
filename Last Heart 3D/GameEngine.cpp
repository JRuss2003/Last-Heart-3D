#include "GameEngine.h"
#include <iostream>
#include "Player.h"


void GameEngine::Init(int x, int y, int width, int height)
{
	isRunning = true;
	Window::Get()->Init(x, y, width, height);
	RenderEngine::Get()->Init();
	RenderEngine::Get()->LoadShaders("GameData/shaders/vertexshader.txt", "GameData/shaders/fragmentshader.txt");
	glUseProgram(RenderEngine::Get()->ProgramID);
	Textures::Get()->Load();
	RenderEngine::Get()->BindTexture(&Textures::Get()->tileset);
	Camera::Get()->Init();
	Player::Get()->x = 700;
	Player::Get()->z = 700;
	Player::Get()->y = 70;
	world.Generate();
	Physics::Get()->physicsQue.push_back(Player::Get());
}

void GameEngine::Update()
{
	Clock::Get()->Tick();
	EventProcessor::Get()->PollEvents();
	Physics::Get()->Update();
	Camera::Get()->Update();
	world.Update();
	Window::Get()->Clear();
	world.Render();
	Window::Get()->Update();
}
