#ifndef SPRITE_H
#define SPRITE_H
#define DLLEXPORT __declspec(dllexport)

#include "Entity2D.h"
#include "Animation.h"

namespace Engine
{
	class DLLEXPORT Sprite : public Entity2D
	{
	private:
		Animation animation;
		vec2 spriteVertex[4];
	public:
		Sprite();
		Sprite(int _x, int _y);
		Sprite(float _x, float _y);
		Sprite(vec2 v);
		void set(Renderer renderer, Color spriteColor);
		void SetAnimation(vec2 imageCount, float switchTime, vec2 startingFrame);
		void UpdateSprite(int row, bool isReversed, float& deltaTime);
		void SetSingleFrame(vec2 framePos);
		void draw();
		vec2 size() { return vec2(animation.getwidth(), animation.getHeight()); }
	};
}

#endif //SPRITE_H
