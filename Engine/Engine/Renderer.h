#ifndef RENDERER_H
#define RENDERER_H

#include "GLFW/glfw3.h"
#include "Color.h"

class Renderer
{
	Color color;
public:
	Renderer(Color _color);
	~Renderer();
	void SetBackground(Color _color);
};

#endif // !RENDERER_H



