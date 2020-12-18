#include "CollisionManager.h"
using namespace std;

Engine::CollisionManager::CollisionManager()
{
	isColliding = false;
}


bool Engine::CollisionManager::CollisionDetection(glm::vec2 entityPos, glm::vec2 entityPos2, glm::vec2 sizeP1, glm::vec2 sizeP2)
{
	float Dx = abs(entityPos.x - entityPos2.x);
	float Dy = abs(entityPos.y - entityPos2.y);


	if (Dx < (sizeP1.x + sizeP2.x) / 2 && Dy < (sizeP1.y + sizeP2.y) / 2) {
		cout << "Collision Detected" << endl;
		return true;
	}
	return false;

	/*if ((entityPos.x <= entityPos2.x + sizeP2.x) &&
		(entityPos.x + sizeP1.x >= entityPos2.x) &&
		(entityPos.y <= entityPos2.y + sizeP2.y) &&
		(entityPos.y + sizeP1.y >= entityPos2.y))
	{
		cout << "Collision Detected" << endl;
		return false;
	}

	return true;*/
}
