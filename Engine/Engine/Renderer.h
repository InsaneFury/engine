#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include "Color.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/transform.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define DLLEXPORT __declspec(dllexport)
typedef unsigned int GLuint;

using namespace std;
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

namespace Engine
{
	class Material;

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
		void UseProgram(unsigned int shader);
		void SetSpriteShaderAttrib(unsigned int shader, GLint posAttrib, GLint colAttrib, GLint texAttrib, GLuint uniModel, glm::mat4 model);
		ShaderProgramSource ShaderParser(const string& filepath);
		unsigned int CompileShader(unsigned int type, const string& source);
		unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
		mat4 GetView();
		GLuint GetUniView();
		void SetUniView(GLuint _uniview);
		mat4 GetProjection();
		GLuint GetUniProj();
		void SetUniProj(GLuint _uniproj);
		void BindBufferSprite(GLuint& VertexBuffer, const GLfloat g_vertex_buffer_data[]);
		void DrawSprite(unsigned int shader, GLuint VertexArrayID, Material texture1, Material texture2, GLuint uniModel, glm::mat4 model);
		
	};
}

#endif // RENDERER_H
