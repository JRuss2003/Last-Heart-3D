#include "Window.h"

void Window::Init(int x, int y, int width, int height)
{
	this->width = width;
	this->height = height;
	//Init glfw
	glewExperimental = true;
	glfwInit();

	//Init opengl
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create window
	window = glfwCreateWindow(width, height, "Last Heart 3D", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);

	
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	crosshairCursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, crosshairCursor);
	glfwSwapInterval(0);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	glfwSwapBuffers(window);
}
