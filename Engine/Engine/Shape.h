#ifndef SHAPE_H
#define SHAPE_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Transform.h"

class DLLEXPORT Shape
{
protected:
	float x;
	float y;
	GLuint VertexArrayID;
	GLuint VertexBuffer;
	unsigned int shader;
	unsigned int texture1;
	unsigned int texture2;
	GLuint uniModel;
	GLuint uniView;
	GLuint uniProj;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
public:
	Shape();
	Shape(float _x, float _y);
	float getX() { return x; };
	float getY() { return y; };
	GLuint GetShader() { return shader; };
	void setX(float _x);
	void setY(float _y);
	void moveTo(float _x, float _y);
	virtual void set(Color shapeColor, const char * pathTexture1, GLenum typeTexture1, bool flipTexture1,
		const char * pathTexture2, GLenum typeTexture2, bool flipTexture2) = 0;
	virtual void draw() = 0;
	Transform transform;
	void rotate(float speed, glm::vec3 _rotation);
	void translate(glm::vec3 _position);
	void scale(glm::vec3 _localScale);
	Renderer currentRenderer;
};

#endif // SHAPE_H