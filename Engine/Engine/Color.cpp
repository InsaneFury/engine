#include "Color.h"

Color::Color(GLclampf _red, GLclampf _green, GLclampf _blue, GLclampf _alpha)
:
red(_red),
green(_green),
blue(_blue),
alpha(_alpha)
{

}

Color::~Color()
{
}

void Color::SetColor(GLclampf _red, GLclampf _green, GLclampf _blue, GLclampf _alpha)
{
	red = _red;
	green = _green;
	blue = _blue;
	alpha = _alpha;
}