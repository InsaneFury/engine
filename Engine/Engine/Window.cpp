#include "Window.h"
#include "Entity2D.h"
#include "Triangle.h"
#include "Input.h"

using namespace Engine;

Window::Window()
{
	window = nullptr;
}

bool Window::Open(int width, int height, const char windowName[64])
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void Window::setRenderer(Renderer _render)
{
	windowRenderer = _render;
}

GLFWwindow* Window::getWindow()
{
	return window;
}

Renderer Engine::Window::getRenderer()
{
	return windowRenderer;
}
