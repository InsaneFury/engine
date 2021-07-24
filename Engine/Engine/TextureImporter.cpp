#include "TextureImporter.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool Engine::TextureImporter::LoadTexture(const char* path, GLuint type, bool flip, GLint FilteringOption,unsigned int& textureOut)
{
	stbi_set_flip_vertically_on_load(true);

	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	glGenTextures(1, &textureOut);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureOut);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilteringOption);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilteringOption);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return true;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		textureOut = 0;
		return false;
	}

	
}
