#include "CollisionManager.h"
using namespace std;

Engine::CollisionManager::CollisionManager()
{
	isColliding = false;
}


bool Engine::CollisionManager::CollisionDetection(glm::vec2 entityPos, glm::vec2 entityPos2, glm::vec2 sizeP1, glm::vec2 sizeP2)
{
	if ((entityPos.x <= entityPos2.x +sizeP2.x) &&
		(entityPos.x + sizeP1.x >= entityPos2.x) &&
		(entityPos.y <= entityPos2.y + sizeP2.y) &&
		(entityPos.y + sizeP1.y >= entityPos2.y))
	{
		cout << "Collision Detected"<<endl;
	}

	return isColliding;
}
