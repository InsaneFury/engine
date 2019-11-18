#include "Renderer.h"
#include "BaseGame.h"
#include <fstream>
#include <sstream>
using namespace Engine;

enum ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

Renderer::Renderer()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 0;
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);
	uniView = 0;
	uniProj = 0;
	SetProjection();
	SetView();
}

ShaderProgramSource Renderer::ShaderParser(const string& filepath)
{
	ifstream stream(filepath);

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };

}

unsigned int Renderer::CompileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Renderer::CreateShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Renderer::SetBackgroundColors(Color backgroundColor)
{
	float red = backgroundColor.GetRed() * RBGTOFLOAT;
	float green = backgroundColor.GetGreen() * RBGTOFLOAT;
	float blue = backgroundColor.GetBlue() * RBGTOFLOAT;
	float alpha = backgroundColor.GetAlpha() * RBGTOFLOAT;

	color.SetColor(red, green, blue, alpha);
}

void Renderer::ChangeBackgroundColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Renderer::DeleteShader(unsigned int shader)
{
	glDeleteProgram(shader);
}

void Renderer::SetShader(unsigned int shader)
{
	glUseProgram(shader);
}

void Renderer::SetProjection()
{
	proj = glm::ortho(
		-1.0f,
		1.f,
		-1.f,
		1.0f,
		0.0f,
		100.f
	);
}

void Renderer::SetView()
{
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 2.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
}

mat4 Renderer::GetProjection()
{
	return proj;
}

GLuint Engine::Renderer::GetUniProj()
{
	return uniProj;
}

void Engine::Renderer::SetUniProj(GLuint _uniproj)
{
	uniProj = _uniproj;
}

mat4 Renderer::GetView()
{
	return view;
}

GLuint Engine::Renderer::GetUniView()
{
	return uniView;
}

void Engine::Renderer::SetUniView(GLuint _uniview)
{
	uniView = _uniview;
}
