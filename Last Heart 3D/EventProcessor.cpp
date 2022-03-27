#include "EventProcessor.h"
#include "GameEngine.h"
#include <cmath>
#include "Player.h"
#include "Clock.h"

void EventProcessor::PollEvents()
{
	Player::Get()->xSpeed = 0.0;
	Player::Get()->ySpeed = 0.0;
	Player::Get()->zSpeed = 0.0;
	glfwPollEvents();
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		GameEngine::Get()->world.OnExit();
		GameEngine::Get()->isRunning = false;
	}
	if(glfwWindowShouldClose(Window::Get()->window) == 1)
		GameEngine::Get()->isRunning = false;
	
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_W) == GLFW_PRESS ) {
		Player::Get()->xSpeed = cos(Player::Get()->angle) * Clock::Get()->deltaTime;
		Player::Get()->zSpeed = sin(Player::Get()->angle) * Clock::Get()->deltaTime;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(Window::Get()->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Player::Get()->xSpeed = cos(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
		Player::Get()->zSpeed = sin(Player::Get()->angle) * Clock::Get()->deltaTime * 4.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_S) == GLFW_PRESS) {
		Player::Get()->xSpeed = -cos(Player::Get()->angle) * Clock::Get()->deltaTime;
		Player::Get()->zSpeed = -sin(Player::Get()->angle) * Clock::Get()->deltaTime;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_A) == GLFW_PRESS) {
		Player::Get()->xSpeed = sin(Player::Get()->angle) * Clock::Get()->deltaTime;
		Player::Get()->zSpeed = -cos(Player::Get()->angle) * Clock::Get()->deltaTime;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_D) == GLFW_PRESS) {
		Player::Get()->xSpeed = -sin(Player::Get()->angle) * Clock::Get()->deltaTime;
		Player::Get()->zSpeed = cos(Player::Get()->angle) * Clock::Get()->deltaTime;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Player::Get()->ySpeed = Clock::Get()->deltaTime * 6.0;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_TAB) == GLFW_PRESS) {
		Player::Get()->ySpeed = -Clock::Get()->deltaTime * 6.0;
	}
	if (glfwGetMouseButton(Window::Get()->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		Player::Get()->MineBlock();
		
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
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_5) == GLFW_PRESS) {
		Player::Get()->blockID = WATER;
	}
	if (glfwGetKey(Window::Get()->window, GLFW_KEY_6) == GLFW_PRESS) {
		Player::Get()->blockID = SAND;
	}
}
