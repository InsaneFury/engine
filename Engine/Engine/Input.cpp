#include "Input.h"

Input::Input()
{
	window = nullptr;
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
