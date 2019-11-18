#include "Input.h"

using namespace Engine;

Input::Input()
{
	window = nullptr;
}

Input::~Input()
{
}

void Input::setWindow(GLFWwindow* _window)
{
	window = _window;
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

bool Input::getKeyDown(int key)
{
	bool keyCurrentlyPressed = glfwGetKey(window, key) == GLFW_PRESS;
	if (!isKeyPressed[key] && keyCurrentlyPressed)
	{
		isKeyPressed[key] = true;
		return true;
	}
	isKeyPressed[key] = keyCurrentlyPressed;
	return false;
}
