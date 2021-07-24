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
	id = -1;
}

Sprite::Sprite(int _x, int _y)
{
	moveTo((float)_x, (float)_y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
	id = -1;
}

Sprite::Sprite(float _x, float _y)
{
	moveTo(_x, _y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
	id = -1;
}

Sprite::Sprite(vec2 pos)
{
	moveTo(pos.x, pos.y, 0);
	VertexArrayID = 0;
	VertexBuffer = 0;
	shader = 0;
	id = -1;
}

void Sprite::set(Renderer renderer, Color spriteColor)
{
	currentRenderer = renderer;

	ShaderProgramSource source = currentRenderer.ShaderParser("res/shaders/Shape.shader");
	shader = currentRenderer.CreateShader(source.vertexSource, source.fragmentSource);
	currentRenderer.UseProgram(shader);

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

	currentRenderer.BindBufferSprite(VertexBuffer,g_vertex_buffer_data);
	currentRenderer.SetSpriteShaderAttrib(shader, posAttrib, colAttrib, texAttrib, uniModel, model);
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
	currentRenderer.DrawSprite(shader, VertexArrayID, texture1, texture2, uniModel, model);
}
