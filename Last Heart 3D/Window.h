#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	void Init(int x, int y, int width, int height);
	void Clear();
	void Update();
	static Window* Get() { static Window gameWindow; return &gameWindow; }
	GLFWwindow* window;
	int width;
	int height;
	GLFWcursor* crosshairCursor;
};
