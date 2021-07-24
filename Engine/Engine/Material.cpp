#include "Material.h"

using namespace Engine;

Material::Material()
{
	texture = 0;
}

Material::~Material()
{

}

void Material::SetTexture(const char* path, GLuint type, bool flip, GLint FilteringOption)
{
	unsigned int newTexture;
	if (TextureImporter::LoadTexture(path, type, flip, FilteringOption, newTexture))
	{
		texture = newTexture;
	}
}

unsigned int Material::GetTexture()
{
	return texture;
}