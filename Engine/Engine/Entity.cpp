#include "Entity.h"

using namespace Engine;

Engine::Entity::~Entity()
{
}



Entity::Entity()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	model = glm::mat4(1.0f);
	libre = true;
}

Entity::Entity(Renderer renderer)
{
	currentRenderer = renderer;
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	model = glm::mat4(1.0f);
	libre = true;
}

Entity::Entity(int _x, int _y, int _z)
{
	moveTo(static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z));
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	model = glm::mat4(1.0f);
	libre = true;
}

Entity::Entity(float _x, float _y, float _z)
{
	moveTo(_x, _y, _z);
	VertexArrayID = 0;
	VertexBuffer = 0;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	uniModel = 0;
	model = glm::mat4(1.0f);
	libre = true;

}

Entity::Entity(vec3 pos)
{
	moveTo(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	VertexArrayID = 0;
	VertexBuffer = 0;
	uniModel = 0;
	model = glm::mat4(1.0f);
	libre = true;
}

float Entity::getX()
{
	return position.x;
}
float Entity::getY()
{
	return position.y;
}
float Entity::getZ()
{
	return position.z;
}
void Entity::setX(float _x)
{
	position.x = _x;
}
void Entity::setY(float _y)
{
	position.y = _y;
}
void Entity::setZ(float _z)
{
	position.z = _z;
}

void Entity::moveTo(float _x, float _y, float _z)
{
	setX(_x);
	setY(_y);
	setZ(_z);
}

void Entity::Rotate(vec3 _rotation)
{
	model = glm::rotate(model, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));
}

void Entity::setPosition(vec3 newTranslation)
{
	//oldPosition = position;
	if (libre)
	{
		oldModel = model;
		model = glm::translate(model, newTranslation);
	}
	else
		model = oldModel;

	GLint m_viewport[4];

	glGetIntegerv(GL_VIEWPORT, m_viewport);
	if (libre)
	{
		oldPosition = position;
		position = glm::project(vec3(newTranslation.x, newTranslation.y, newTranslation.z), model, currentRenderer.GetProjection(), vec4(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]));
	}
	else
		position = oldPosition;
}

vec3 Entity::getPosition()
{
	return position;
}

void Entity::Scale(vec3 _scale)
{
	model = glm::scale(model, _scale);
}
