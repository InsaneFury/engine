#pragma warning(push)

#pragma warning(disable:4251)


#ifndef ENTITY_H
#define ENTITY_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Window.h"
#include "CollisionManager.h"

namespace Engine
{
	class DLLEXPORT Entity
	{
	protected:
		vec3 position;
		mat4 testPosition;
		GLuint VertexArrayID;
		GLuint VertexBuffer;
		GLuint uniModel;
		GLint posAttrib;
		GLint colAttrib;
		GLint texAttrib;
		mat4 model;

	public:
		Entity();
		Entity(Renderer renderer);
		~Entity();
		Entity(int _x, int _y, int _z);
		Entity(float _x, float _y, float _z);
		Entity(vec3 pos);
		void setPosition(vec3 pos);
		vec3 getPosition();
		float getX();
		float getY();
		float getZ();
		void setX(float _x);
		void setY(float _y);
		void setZ(float _z);
		void moveTo(float _x, float _y, float _z);
		virtual void set(Renderer renderer, Color shapeColor);
		virtual void draw();
		void endDraw();
		void Rotate(vec3 _rotation);
		void Scale(vec3 _scale);
		Renderer currentRenderer;
		CollisionManager BoxCollider;
	};
}

#endif //ENTITY_H

#pragma warning(pop)