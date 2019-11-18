#ifndef MATERIAL_H
#define MATERIAL_H
#define DLLEXPORT __declspec(dllexport)

#include "stb_image.h"
#include "Window.h"

namespace Engine // Shaders que se van a usar, destruye su shader, bindea shaders, 
{
	class DLLEXPORT Material
	{
	private:
		unsigned int texture;
	public:
		Material();
		~Material();
		void SetTexture(const char* path, GLuint type, bool flip, GLint FilteringOption);
		unsigned int GetTexture();
	};
}

#endif //MATERIAL_H
