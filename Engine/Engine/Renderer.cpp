#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetBackground(Color _color)
{
	glClearColor(_color.GetRed(), _color.GetGreen(), _color.GetBlue(), _color.GetAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}
