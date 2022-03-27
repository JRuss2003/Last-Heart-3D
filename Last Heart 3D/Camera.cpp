#include "Camera.h"
#include "Window.h"
#include "RenderEngine.h"
#include "Player.h"

void Camera::Init()
{
	angleY = 2.0;
	angle = 0.0;
	camX = Player::Get()->x;
	camY = Player::Get()->y;
	camZ = Player::Get()->z;
	projection = glm::perspective(glm::radians(60.0f), (float)Window::Get()->Window::Get()->width / (float)Window::Get()->Window::Get()->height, 0.1f, 1200.0f);
	view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(camX + cos(angle), camY + tan(angleY), camZ + sin(angle)), glm::vec3(0.0, 1.0, 0.0));
	MatrixID = glGetUniformLocation(RenderEngine::Get()->ProgramID, "MVP");
}

void Camera::Update()
{
	camX = Player::Get()->x;
	camY = Player::Get()->y;
	camZ = Player::Get()->z;
	Camera::Get()->Rotate();
	view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(camX + cos(angle), camY + tan(angleY), camZ + sin(angle)), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::Rotate()
{
	prevYpos = ypos;
	prevXpos = xpos;
	glfwGetCursorPos(Window::Get()->window, &xpos, &ypos);

	if (ypos < prevYpos) {

		if (Camera::Get()->angleY < 1.4)
			Camera::Get()->angleY += 0.0030 * (prevYpos - ypos);

	}
	if (ypos > prevYpos) {
		if (Camera::Get()->angleY > -1.4)
			Camera::Get()->angleY -= 0.0030 * (ypos - prevYpos);
	}

	if (xpos < prevXpos) {

		Camera::Get()->angle -= 0.0030 * (prevXpos - xpos);
		glfwSetCursorPos(Window::Get()->window, Window::Get()->width / 2, Window::Get()->height / 2);
		xpos = Window::Get()->width / 2;
		ypos = Window::Get()->height / 2;
	}
	if (xpos > prevXpos) {
		Camera::Get()->angle += 0.0030 * (xpos - prevXpos);
		glfwSetCursorPos(Window::Get()->window, Window::Get()->width / 2, Window::Get()->height / 2);
		xpos = Window::Get()->width / 2;
		ypos = Window::Get()->height / 2;
	}


	Player::Get()->angle = this->angle;
	Player::Get()->angleY = this->angleY;
}
