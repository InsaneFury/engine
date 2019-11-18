#ifndef INPUT_H
#define INPUT_H
#include "Window.h"
#define DLLEXPORT __declspec(dllexport)

namespace Engine
{
	class DLLEXPORT Input
	{
	private:
		GLFWwindow * window;
		bool isKeyPressed[348] = { false };
	public:
		Input();
		~Input();
		void setWindow(GLFWwindow* _window);
		bool getKey(int key);
		bool getKeyDown(int key);
	};
}

#endif // INPUT_H