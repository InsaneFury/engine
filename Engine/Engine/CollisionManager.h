#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#define DLLEXPORT __declspec(dllexport)

#include <iostream>
#include <glm.hpp>

namespace Engine
{
	class DLLEXPORT CollisionManager
	{
	private:
		bool isColliding;
	public:
		CollisionManager();
	
		bool CollisionDetection(glm::vec2 entityPos, glm::vec2 entityPos2, glm::vec2 sizeP1, glm::vec2 sizeP2);
	};
}



#endif // COLLISIONMANAGER_H
