#ifndef INPUT_H
#define INPUT_H
#include "Window.h"
#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT Input
{
	GLFWwindow* window;
public:
	Input();
	void setWindow(GLFWwindow* current);
	bool getKey(int key);
};

#endif //INPUT_H

