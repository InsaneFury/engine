#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

void Renderer::DrawTriangle()
{
	// Shader sources
	const GLchar* vertexSource = R"glsl(
    #version 150 core
	uniform vec2 pos;
    in vec2 position;

    void main()
    {
		gl_Position = vec4(position + pos, 0.0, 1.0);
    }
)glsl";

	const GLchar* fragmentSource = R"glsl(
    #version 150 core

	uniform vec3 triangleColor;

	out vec4 outColor;

    void main()
    {
		outColor = vec4(triangleColor, 1.0);
    }
)glsl";


	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	GLfloat vertices[] =
	{
		0.0f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

	glDrawArrays(GL_TRIANGLES, 0, 3);

	
}
