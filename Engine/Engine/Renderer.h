#ifndef RENDERER_H
#define RENDERER_H
#define DLLEXPORT __declspec(dllexport)

#include <iostream>
#include "GLFW/glfw3.h"
#include "Color.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/transform.hpp>

typedef unsigned int GLuint;

using namespace std;

struct ShaderProgramSource
{
	string vertexSource;
	string fragmentSource;
};


class DLLEXPORT Renderer
{
public:
	Renderer();
	ShaderProgramSource ShaderParser(const string& filepath);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
	void SetBackground(Color _color);
};

#endif // !RENDERER_H



