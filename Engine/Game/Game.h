#ifndef GAME_H
#define GAME_H
#include "BaseGame.h"
#define DLLEXPORT __declspec(dllexport)


namespace Engine
{
	class DLLEXPORT Game : public BaseGame
	{
	private:
		bool isRotated;
		bool isRotated2;
		ColorList Colors;
		Triangle triangle;
		Triangle triangle2;
		Sprite sprite;
		Sprite sprite2;
		float timer;
		float timerSprite;
	public:
		Game();
		~Game();
		void InitGame();
		void Update(Time deltaTime);
		//void init();

	};
}

#endif // GAME_H