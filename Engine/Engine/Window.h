#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"

class Window
{
	GLFWwindow* window;
public:
	Window();
	~Window();
	int CreateWindow();
	GLFWwindow* GetWindow() { return window; }
};

#endif // !WINDOW_H

