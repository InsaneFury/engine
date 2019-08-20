#include "Renderer.h"

Renderer::Renderer(Color _color)
:
color(_color)
{
}

Renderer::~Renderer()
{
}

void Renderer::SetBackground(Color _color)
{
	color = _color;
}
