#ifndef COLOR_H
#define COLOR_H
#include "GLFW/glfw3.h"

class Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;

public:
	Color(GLclampf _red, GLclampf green, GLclampf blue, GLclampf alpha);
	~Color();
	void SetColor(GLclampf _red, GLclampf green, GLclampf blue, GLclampf alpha);
	GLfloat GetRed() { return red; }
	GLfloat GetGreen() { return green; }
	GLfloat GetBlue() { return blue; }
	GLfloat GetAlpha() { return alpha; }
};
#endif // COLOR_H

