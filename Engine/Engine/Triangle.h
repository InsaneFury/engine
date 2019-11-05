#ifndef TRIANGLE_H
#define TRIANGLE_H
#define DLLEXPORT __declspec(dllexport)

#include "Shape.h"

class DLLEXPORT Triangle : public Shape
{

	public:
		Triangle();
		Triangle(float _x, float _y);
		void set(Color triangleColor, const char * pathTexture1, GLenum typeTexture1, bool flipTexture1,
				 const char * pathTexture2, GLenum typeTexture2, bool flipTexture2);
		void draw();
};

#endif //TRIANGLE_H
