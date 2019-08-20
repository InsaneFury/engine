#include "BaseGame.h"
#include <GLFW/glfw3.h>
#include "Window.h"

BaseGame::BaseGame()
{

}
int BaseGame::InitWindow() 
{
	Window window;
	window.CreateWindow();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}