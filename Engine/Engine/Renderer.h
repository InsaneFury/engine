#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include "Color.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/transform.hpp"


#define DLLEXPORT __declspec(dllexport)
typedef unsigned int GLuint;

using namespace std;
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

namespace Engine
{

	struct ShaderProgramSource
	{
		string vertexSource;
		string fragmentSource;
	};

	class DLLEXPORT Renderer
	{
	private:
		Color color;
		float _red;
		float _green;
		float _blue;
		float _alpha;
		mat4 view;
		mat4 proj;
		GLuint uniView;
		GLuint uniProj;
		void SetProjection();
		void SetView();
	public:
		Renderer();
		void SetBackgroundColors(Color backgroundColor);
		void ChangeBackgroundColor();
		void DeleteShader(unsigned int shader);
		void SetShader(unsigned int shader);
		ShaderProgramSource ShaderParser(const string& filepath);
		unsigned int CompileShader(unsigned int type, const string& source);
		unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
		mat4 GetView();
		GLuint GetUniView();
		void SetUniView(GLuint _uniview);
		mat4 GetProjection();
		GLuint GetUniProj();
		void SetUniProj(GLuint _uniproj);
	};
}

#endif // RENDERER_H
