#ifndef TRANSFORM_H
#define TRANSFORM_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"

using namespace glm;

class DLLEXPORT Transform
{
public:
	Transform();
	vec3 rotation;
	vec3 position;
	vec3 localScale;
};
#endif //TRANSFORM_H

