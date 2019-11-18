#ifndef BASEGAME_H
#define BASEGAME_H
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity2D.h"
#include "Triangle.h"
#include "Sprite.h"
#include "Time.h"
#include "Color.h"
#include "ColorList.h"


#define DLLEXPORT __declspec(dllexport)

using namespace std;

namespace Engine
{

	class DLLEXPORT BaseGame 
	{
	private:
		Window _window;
		Renderer _render;
		int _windowwidth;
		int _windowHeight;
		float _lastFrameTime = 0.0f;
	protected:
		Input input;
	public:
		BaseGame();
		void Init(int width, int height, string windowName);
		void GameLoop();
		void SetBackgroundColors(Color backgroundColor);
		bool WindowIsClosed();
		void DeInit();
		void SwapBuffers();
		void UpdateBackgroud();
		Renderer GetRenderer();
		virtual void Update(Time deltaTime) = 0;
	};
}

#endif // BASEGAME_H