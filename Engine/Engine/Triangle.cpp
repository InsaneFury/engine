#include "GL/glew.h"
#include "Triangle.h"
#include "stb_image.h"

#include "Vertex.h"



unsigned int CreateTexture(const char* path, GLenum type, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);

	int width;
	int height;
	int nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, texture);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}



	stbi_image_free(data);

	return texture;
}


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

void Triangle::set(Color triangleColor, const char * pathTexture1, GLenum typeTexture1, bool flipTexture1,
				   const char * pathTexture2, GLenum typeTexture2, bool flipTexture2)
{

	texture1 = CreateTexture(pathTexture1, typeTexture1,flipTexture1);
	texture2 = CreateTexture(pathTexture2,typeTexture2, flipTexture2);

	Vertex triangleVertexs[3];

	Vertex texCoords[] =
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.5f, 1.0f }
	};



	triangleVertexs[0] = { -0.5f, -0.5f };
	triangleVertexs[1] = { 0.5f, -0.5f };
	triangleVertexs[2] = { 0.0f, 0.5f };

	GLfloat red =triangleColor.GetRed();
	GLfloat green = triangleColor.GetGreen();
	GLfloat blue = triangleColor.GetBlue();
	GLfloat alpha = triangleColor.GetAlpha();

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] =
	{
		   triangleVertexs[0].x, triangleVertexs[0].y, red, green, blue, alpha,  texCoords[0].x, texCoords[0].y,
		   triangleVertexs[1].x, triangleVertexs[1].y, red, green, blue, alpha,  texCoords[1].x, texCoords[1].y,
		   triangleVertexs[2].x, triangleVertexs[2].y, red, green, blue, alpha,  texCoords[2].x, texCoords[2].y
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

	
	ShaderProgramSource source = currentRenderer.ShaderParser("shaders/Shape.shader");
	shader = currentRenderer.CreateShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);

	GLint posAttrib = glGetAttribLocation(shader, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shader, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


	GLint texAttrib = glGetAttribLocation(shader, "texturePos");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
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
	glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader, "texture2"), 1); 
}

void Triangle::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}


