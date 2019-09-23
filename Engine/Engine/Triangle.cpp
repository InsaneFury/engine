#include "GL/glew.h"
#include "Triangle.h"
#include "stb_image.h"

#include "Vertex.h"

Triangle::Triangle()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

Triangle::Triangle(float _x, float _y)
{
	moveTo(_x, _y);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

void Triangle::set(Color triangleColor)
{
	
	float texCoords[] =
	{
		0.0f, 0.0f,  
		1.0f, 0.0f,  
		0.5f, 1.0f   
	};

	Vertex triangleVertexs[3];


	triangleVertexs[0].x = -0.5f;
	triangleVertexs[0].y = -0.5f;
	triangleVertexs[1].x = 0.5f;
	triangleVertexs[1].y = -0.5f;
	triangleVertexs[2].x = 0.0f;
	triangleVertexs[2].y = 0.5f;


	float red = static_cast<float>(triangleColor.GetRed()) * 0.004f;
	float green = static_cast<float>(triangleColor.GetGreen()) * 0.004f;
	float blue = static_cast<float>(triangleColor.GetBlue()) * 0.004f;
	float alpha = static_cast<float>(triangleColor.GetAlpha()) * 0.004f;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] =
	{
		   triangleVertexs[0].x, triangleVertexs[0].y, red, green, blue, alpha, 0.0f, 0.0f,
		   triangleVertexs[1].x, triangleVertexs[1].y, red, green, blue, alpha, 1.0f, 0.0f,
		   triangleVertexs[2].x, triangleVertexs[2].y, red, green, blue, alpha, 0.5f, 1.0f
	};

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] =
	{
		0, 1, 2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	ShaderProgramSource source = currentRenderer.ShaderParser("res/shaders/Shape.shader");
	shader = currentRenderer.CreateShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);

	GLint posAttrib = glGetAttribLocation(shader, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shader, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	uniModel = glGetUniformLocation(shader, "model");
	model = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -2.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f) 
	);

	GLint uniView = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	proj = glm::ortho(
		-1.0f,
		1.f,
		-1.f,
		1.0f,
		0.0f,
		100.f
	);
	GLint uniProj = glGetUniformLocation(shader, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void Triangle::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}


