#include "Shape.h"

Shape::Shape()
{
	VertexArrayID=0;
	VertexBuffer=0;
	shader=0;
}

Shape::Shape(float _x, float _y)
{
	moveTo(_x, _y);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

void Shape::setX(float _x)
{
	x = _x;
}

void Shape::setY(float _y)
{
	y = _y;
}

void Shape::moveTo(float _x, float _y)
{
	x = _x;
	y = _y;
}
void Shape::rotate(float speed, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(speed), axis);
}

void Shape::translate(glm::vec3 pos)
{
	model = glm::translate(model, pos);
}
void Shape::scale(glm::vec3 factor)
{
	model = glm::scale(model, factor);
}