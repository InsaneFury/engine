#include "Input.h"

Input::Input()
{
	window = nullptr;
}

void Input::setWindow(GLFWwindow* current) 
{
	window = current;
}

bool Input::getKey(int key)
{
	int state = glfwGetKey(window, key);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	return false;
}
