#include "BaseGame.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include "Color.h"
BaseGame::BaseGame()
{

}
int BaseGame::InitWindow() 
{
	Window window;
	window.CreateWindow();
	Renderer* render = new Renderer();
	Color bgColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Render here */
		render->SetBackground(bgColor);

		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	
	glfwTerminate();
	delete render;
	return 0;
}