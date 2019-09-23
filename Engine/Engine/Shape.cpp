#include "Shape.h"

Shape::Shape()
	:
	VertexArrayID(0),
	VertexBuffer(0),
	shader(0)
{
}

Shape::Shape(float _x, float _y)
	:
	VertexArrayID(0),
	VertexBuffer(0),
	shader(0)
{
	moveTo(_x, _y);
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
