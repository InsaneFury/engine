#include "Animation.h"

using namespace Engine;


/*
	Las cordenadas de las texturas llevan la siguiente representacion.
	0 -> bottom-left
	1 ->  bottom-right
	2 -> top-right
	3 -> top-left
*/


Animation::Animation()
{

}

Animation::Animation(Material texture, vec2 imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x = 0;
	currentImage.y = 0;

	glGetTexLevelParameteriv(texture.GetTexture(), 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(texture.GetTexture(), 0, GL_TEXTURE_HEIGHT, &height);

	finalSize.x = 1 / imageCount.x;
	finalSize.y = 1 / imageCount.y;


}

void Animation::Update(int row, float &deltaTime)
{
	currentImage.y = row;
	totalTime = deltaTime;
	

	if (totalTime >= switchTime)
	{
		totalTime = 0;
		deltaTime = 0;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}



	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y }; 
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y };
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; 
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) }; 
}

void Animation::UpdateReverse(int row, float& deltaTime)
{
	currentImage.y = row;
	totalTime = deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime = 0;
		deltaTime = 0;
		currentImage.x--;

		if (currentImage.x <= 0)
		{
			currentImage.x = imageCount.x;
		}
	}

	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y };
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y }; 
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; 
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) };
}

void Animation::SetSingleFrame(vec2 framePos)
{
	currentImage = framePos;

	newTexCoords[0] = { finalSize.x * currentImage.x, finalSize.y * currentImage.y }; 
	newTexCoords[1] = { finalSize.x * (currentImage.x + 1), finalSize.y * currentImage.y };
	newTexCoords[2] = { finalSize.x * (currentImage.x + 1), finalSize.y * (currentImage.y + 1) }; 
	newTexCoords[3] = { finalSize.x * currentImage.x, finalSize.y * (currentImage.y + 1) }; 
}