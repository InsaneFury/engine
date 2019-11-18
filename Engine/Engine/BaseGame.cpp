#include "BaseGame.h"
#include "Renderer.h"

using namespace Engine;

BaseGame::BaseGame()
{
	_windowwidth = 0;
	_windowHeight = 0;
}

void BaseGame::Init(int width, int height, string windowName)
{
	_window.setRenderer(_render);
	_window.Open(width, height, windowName.c_str());
	input.setWindow(_window.getWindow());
}

void BaseGame::GameLoop()
{
	while (!WindowIsClosed())
	{
		float time = (float)glfwGetTime();
		Time Time = time - _lastFrameTime;
		_lastFrameTime = time;

		UpdateBackgroud();

		Update(Time);

		SwapBuffers();
	}

	DeInit();
}

void BaseGame::SetBackgroundColors(Color backgroundColor)
{
	_render.SetBackgroundColors(backgroundColor);
}

bool BaseGame::WindowIsClosed()
{
	return glfwWindowShouldClose(_window.getWindow());
}

void BaseGame::DeInit()
{
	glfwTerminate();
}

void BaseGame::SwapBuffers()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(_window.getWindow());
	/* Poll for and process events */
	glfwPollEvents();
}

void BaseGame::UpdateBackgroud()
{
	/* Render here */
	_render.ChangeBackgroundColor();
}

Renderer BaseGame::GetRenderer()
{
	return _render;
}
