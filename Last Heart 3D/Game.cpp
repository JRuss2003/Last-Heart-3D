#include "Game.h"
#include "Player.h"

Game::Game()
{
	GameEngine::Get()->Init(10, 10, 1920, 1080);
	GameLoop();
}

void Game::GameLoop()
{
	
	while(GameEngine::Get()->isRunning) {
		GameEngine::Get()->Update();
	}
}
