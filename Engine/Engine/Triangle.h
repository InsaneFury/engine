#ifndef TRIANGLE_H
#define TRIANGLE_H
#define DLLEXPORT __declspec(dllexport)

#include "Shape.h"

class DLLEXPORT Triangle : public Shape
{

	public:
		Triangle();
		Triangle(float _x, float _y);
		void set(Color triangleColor);
		void draw();
};

#endif //TRIANGLE_H
