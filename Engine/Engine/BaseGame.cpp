#include "BaseGame.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include "Color.h"
#include "Triangle.h"
#include "Input.h"
BaseGame::BaseGame()
{

}
int BaseGame::InitWindow() 
{
	Window window;
	window.CreateWindow();
	Renderer render;
	Input input;
	input.setWindow(window.GetWindow());
	Color bgColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
	Color tColor = Color(1.0f, 1.0f, 1.0f,1.0f);
	Triangle triangle;
	triangle.currentRenderer = render;
	triangle.set(tColor, "textures/pikachu.jpg", GL_RGB, true, "textures/capi.png", GL_RGBA, true );

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;

	double a = 0;
	double speed = 0.1;

	float x = 0;
	float y = 0;
	float xRotate = 0;
	int blinkSpeed = 200;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		if (a < blinkSpeed) {
			a++;
		}
		
		currentFrame += glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		x = (sin(a *deltaTime * speed) * 0.8f);
		y = (cos(a *deltaTime * speed) * 0.8f);
		xRotate += deltaTime;

		bgColor = Color(x, y, 1.0f, 1.0f);
		

		/* Render here */
		render.SetBackground(bgColor);
		triangle.draw();

		triangle.rotate(1, glm::vec3(xRotate, 0.0f, 0.0f));

		if (input.getKey(GLFW_KEY_E))
		{
			triangle.rotate(1, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		if (input.getKey(GLFW_KEY_Q))
		{
			triangle.rotate(-1, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		if (input.getKey(GLFW_KEY_W))
		{
			triangle.translate(glm::vec3(.0f, .01f, .0f));
		}

		if (input.getKey(GLFW_KEY_S))
		{
			triangle.translate(glm::vec3(.0f, -.01f, .0f));
		}

		if (input.getKey(GLFW_KEY_A))
		{
			triangle.translate(glm::vec3(.01f, .0f, .0f));
		}

		if (input.getKey(GLFW_KEY_D))
		{
			triangle.translate(glm::vec3(-.01f, .0f, .0f));
		}

		if (input.getKey(GLFW_KEY_Z))
		{
			triangle.scale(glm::vec3(1.01f, 1.01f, 1.01f));
		}

		if (input.getKey(GLFW_KEY_X))
		{
			triangle.scale(glm::vec3(.99f, .99f, .99f));
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(triangle.GetShader());
	glfwTerminate();
	return 0;
}