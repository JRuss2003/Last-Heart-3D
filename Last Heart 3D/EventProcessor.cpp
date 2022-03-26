#include "EventProcessor.h"
#include "GameEngine.h"
#include <cmath>
#include "Player.h"
#include "Clock.h"

void EventProcessor::PollEvents()
{
	glfwPollEvents();
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		GameEngine::Get()->world.OnExit();
		GameEngine::Get()->isRunning = false;
	}
	if(glfwWindowShouldClose(Window::Get()->window) == 1)
		GameEngine::Get()->isRunning = false;
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(Window::Get()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Player::Get()->x += cos(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
		Player::Get()->z += sin(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_W) == GLFW_PRESS ) {
		Player::Get()->x += cos(Player::Get()->angle) * Clock::Get()->deltaTime;
		Player::Get()->z += sin(Player::Get()->angle) * Clock::Get()->deltaTime;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_S) == GLFW_PRESS) {
		Player::Get()->x -= cos(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
		Player::Get()->z -= sin(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_A) == GLFW_PRESS) {
		Player::Get()->x += sin(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
		Player::Get()->z -= cos(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_D) == GLFW_PRESS) {
		Player::Get()->x -= sin(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
		Player::Get()->z += cos(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Player::Get()->y += Clock::Get()->deltaTime * 2.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_TAB) == GLFW_PRESS && GameEngine::Get()->world.worldData[((int)Player::Get()->z / 64) * WORLD_SIZE + ((int)Player::Get()->x / 64)].blocks[((int)(Player::Get()->x) % 64) / 2][(int)(Player::Get()->y - (2.0 + Clock::Get()->deltaTime * 2.0)) / 2][((int)(Player::Get()->z) % 64) / 2].solid != true) {
		Player::Get()->y -= Clock::Get()->deltaTime * 2.0;
	}
	if (glfwGetMouseButton(Window::Get()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		Player::Get()->MineBlock();
		
	}
	else {
		threadOn = false;
	}
	if (glfwGetMouseButton(Window::Get()->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		Player::Get()->BuildBlock();
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_0) == GLFW_PRESS) {
		Player::Get()->blockID = GRASS;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_1) == GLFW_PRESS) {
		Player::Get()->blockID = DIRT;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_2) == GLFW_PRESS) {
		Player::Get()->blockID = BRICK;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_3) == GLFW_PRESS) {
		Player::Get()->blockID = WOOD;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_4) == GLFW_PRESS) {
		Player::Get()->blockID = STONE;
	}
}
