#include "Sprite.h"
#include <fstream>
#include <sstream>
#include "Window.h"

using namespace Engine;

Sprite::Sprite()
{
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

Sprite::Sprite(int _x, int _y)
{
	moveTo((float)_x, (float)_y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

Sprite::Sprite(float _x, float _y)
{
	moveTo(_x, _y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

Sprite::Sprite(vec2 pos)
{
	moveTo(pos.x, pos.y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
}

void Sprite::set(Renderer renderer, Color spriteColor)
{
	currentRenderer = renderer;
	ShaderProgramSource source = currentRenderer.ShaderParser("res/shaders/Shape.shader");
	shader = currentRenderer.CreateShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);

	mat4 proj = currentRenderer.GetProjection();
	mat4 view = currentRenderer.GetView();

	vec2 texCoords[] =
	{
		{ 0.0f, 0.0f }, // bottom-left
	{ 0.125f, 0.0f }, // bottom-right
	{ 0.125f, 0.5f }, // top-right
	{ 0.0f, 0.5f } // top-left
	};

	spriteVertex[0] = { -0.1f, -0.1f };
	spriteVertex[1] = { 0.1f, -0.1f };
	spriteVertex[2] = { 0.1f, 0.1f };
	spriteVertex[3] = { -0.1f, 0.1f };


	red = spriteColor.GetRed() * RBGTOFLOAT;
	green = spriteColor.GetGreen() * RBGTOFLOAT;
	blue = spriteColor.GetBlue() * RBGTOFLOAT;
	alpha = spriteColor.GetAlpha() * RBGTOFLOAT;



	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	const GLfloat g_vertex_buffer_data[] =
	{
		spriteVertex[0].x, spriteVertex[0].y, red, green, blue, alpha, texCoords[0].x, texCoords[0].y,
		spriteVertex[1].x, spriteVertex[1].y, red, green, blue, alpha, texCoords[1].x, texCoords[1].y,
		spriteVertex[2].x, spriteVertex[2].y, red, green, blue, alpha, texCoords[2].x, texCoords[2].y,
		spriteVertex[3].x, spriteVertex[3].y, red, green, blue, alpha, texCoords[3].x, texCoords[3].y
	};


	// Identificar el vertex buffer
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &VertexBuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] =
	{
		0, 1, 2, 3
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);



	posAttrib = glGetAttribLocation(shader, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	colAttrib = glGetAttribLocation(shader, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	texAttrib = glGetAttribLocation(shader, "texturePos");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	uniModel = glGetUniformLocation(shader, "model");
	model = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	currentRenderer.SetUniView(glGetUniformLocation(shader, "view"));
	glUniformMatrix4fv(currentRenderer.GetUniView(), 1, GL_FALSE, glm::value_ptr(view));

	currentRenderer.SetUniProj(glGetUniformLocation(shader, "proj"));
	glUniformMatrix4fv(currentRenderer.GetUniProj(), 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(glGetUniformLocation(shader, "texture1"), 0); // set it manually
	glUniform1i(glGetUniformLocation(shader, "texture2"), 1); // set it manually

}

void Sprite::UpdateSprite(int row, bool isReversed, float& deltaTime)
{
	if (isReversed)
	{
		animation.UpdateReverse(row, deltaTime);
	}
	else
	{
		animation.Update(row, deltaTime);
	}

	const GLfloat g_vertex_buffer_data[] =
	{
		spriteVertex[0].x, spriteVertex[0].y, red, green, blue, alpha, animation.newTexCoords[0].x, animation.newTexCoords[0].y,
		spriteVertex[1].x, spriteVertex[1].y, red, green, blue, alpha, animation.newTexCoords[1].x, animation.newTexCoords[1].y,
		spriteVertex[2].x, spriteVertex[2].y, red, green, blue, alpha, animation.newTexCoords[2].x, animation.newTexCoords[2].y,
		spriteVertex[3].x, spriteVertex[3].y, red, green, blue, alpha, animation.newTexCoords[3].x, animation.newTexCoords[3].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sprite::SetSingleFrame(vec2 framePos)
{
	animation.SetSingleFrame(framePos);

	const GLfloat g_vertex_buffer_data[] =
	{
		spriteVertex[0].x, spriteVertex[0].y, red, green, blue, alpha, animation.newTexCoords[0].x, animation.newTexCoords[0].y,
		spriteVertex[1].x, spriteVertex[1].y, red, green, blue, alpha, animation.newTexCoords[1].x, animation.newTexCoords[1].y,
		spriteVertex[2].x, spriteVertex[2].y, red, green, blue, alpha, animation.newTexCoords[2].x, animation.newTexCoords[2].y,
		spriteVertex[3].x, spriteVertex[3].y, red, green, blue, alpha, animation.newTexCoords[3].x, animation.newTexCoords[3].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sprite::SetAnimation(vec2 imageCount, float switchTime, vec2 startingFrame)
{
	Animation newAnimation(texture1, imageCount, switchTime);
	animation = newAnimation;
	SetSingleFrame(startingFrame);
}

void Sprite::draw()
{
	glUseProgram(shader);
	glBindVertexArray(VertexArrayID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1.GetTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2.GetTexture());
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}
