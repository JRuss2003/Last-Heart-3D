#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	void Init();
	void Update();
	void Rotate();
	static Camera* Get() { static Camera camera; return &camera; }
	GLuint MatrixID;
	glm::mat4 projection;
	glm::mat4 view;
	float camX;
	float camY;
	float camZ;
	float angle;
	float angleY;
	double xpos, ypos;
	double prevXpos, prevYpos;
};
