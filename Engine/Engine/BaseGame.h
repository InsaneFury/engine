#ifndef BASE_GAME
#define BASE_GAME

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT BaseGame
{
public:
	 BaseGame();
	 int InitWindow();
};

#endif //BASE_GAME

