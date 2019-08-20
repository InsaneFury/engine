#ifndef COLOR_H
#define COLOR_H
#include "GLFW/glfw3.h"

class Color
{
	GLclampf red;
	GLclampf green;
	GLclampf blue;
	GLclampf alpha;

public:
	Color(GLclampf _red, GLclampf green, GLclampf blue, GLclampf alpha);
	~Color();
	void SetColor(GLclampf _red, GLclampf green, GLclampf blue, GLclampf alpha);
	GLclampf GetRed() { return red; }
	GLclampf GetGreen() { return green; }
	GLclampf GetBlue() { return blue; }
	GLclampf GetAlpha() { return alpha; }
};
#endif // COLOR_H

