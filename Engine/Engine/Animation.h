#ifndef ANIMATION_H
#define ANIMATION_H
#define DLLEXPORT __declspec(dllexport)

#include "Renderer.h"
#include "Material.h"

namespace Engine
{
	class DLLEXPORT Animation
	{
	private:
		vec2 imageCount;
		vec2 currentImage;
		vec2 finalSize;
		float totalTime;
		float switchTime;
		int width;
		int height;

	public:
		Animation();
		Animation(Material texture, vec2 imageCount, float switchTime);
		void Update(int row, float& deltaTime);
		void UpdateReverse(int row, float& deltaTime);
		void SetSingleFrame(vec2 framePos);
		vec2 newTexCoords[4];
		float getwidth() { return (finalSize.x * currentImage.x +1)*50; }
		float getHeight() { return (finalSize.y * currentImage.y + 1)*50; }

	};
}



#endif // ANIMATION_H
