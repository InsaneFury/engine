#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#define DLLEXPORT __declspec(dllexport)

#include "Window.h"

namespace Engine
{
	class DLLEXPORT TextureImporter
	{
	public:
		static bool LoadTexture(const char* path, GLuint type, bool flip, GLint FilteringOption, unsigned int &textureOut);
	};
}

#endif // TEXTUREIMPORTER_H
