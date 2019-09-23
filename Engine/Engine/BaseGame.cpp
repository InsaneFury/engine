#include "BaseGame.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include "Color.h"
#include "Triangle.h"
BaseGame::BaseGame()
{

}
int BaseGame::InitWindow() 
{
	Window window;
	window.CreateWindow();
	Renderer render;
	Color bgColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
	Color tColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
	Triangle triangle;
	triangle.currentRenderer = render;
	triangle.set(tColor);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Render here */
		render.SetBackground(bgColor);
		//triangle.draw();
		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(triangle.GetShader());
	glfwTerminate();
	return 0;
}