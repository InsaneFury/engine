#ifndef RENDERER_H
#define RENDERER_H

#include "GLFW/glfw3.h"
#include "Color.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void SetBackground(Color _color);
	void DrawTriangle();
};

#endif // !RENDERER_H



