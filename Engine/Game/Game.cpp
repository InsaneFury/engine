#include "Game.h"

using namespace Engine;

Game::Game()
{

}

Game::~Game()
{

}

void Game::InitGame()
{
	timerSprite = 0;
	Color red;
	red.SetColor(255, 0, 0, 255);
	SetBackgroundColors(Colors.Gray);
	Init(1024, 720, "Best Game");

	sprite.set(GetRenderer(), Colors.White);
	sprite.SetMaterial1("res/textures/Male1.png", GL_RGBA, true, GL_NEAREST);
	sprite.setPosition(vec3(0.0, 1, 0));
	sprite.SetAnimation(vec2(6, 6), 0.1f, vec2(1, 1));
	sprite.Scale(vec3(1.0f, 1.0f, 1.0f));

	sprite2.set(GetRenderer(), Colors.White);
	sprite2.SetMaterial1("res/textures/ryu.png", GL_RGBA, true, GL_NEAREST);
	sprite2.setPosition(vec3(0.f, 0, 0));
	sprite2.SetAnimation(vec2(9,1), 0.1f, vec2(0,0));
	sprite2.Scale(vec3(2.0f, 2.0f, 2.0f));
	
	tilemap.Set(GetRenderer(), Colors.White, "res/textures/superSS.png",vec2(2,2), vec2(19,19), vec2(.2f, .2f),"res/textures/MapSS.csv");
	//tile2.Set(GetRenderer(), Colors.White, "res/textures/superSS.png", vec2(2, 2), vec2(32, 32));
	GameLoop();
}

void Game::Update(Time deltaTime)
{
	timerSprite += deltaTime;
	timer += deltaTime;
	
	//cout << sprite.libre << endl;
	//sprite.BoxCollider.CollisionDetection(sprite.getPosition(), sprite2.getPosition(), sprite.size(), sprite2.size());
	//cout << "Player Size: " << sprite.size().x << " " << sprite.size().y << endl;

	if (input.getKey(GLFW_KEY_D))
	{
		sprite.UpdateSprite(4, false, timer);
		sprite.setPosition(vec3(1 * deltaTime, 0, 0));
	}
	
	if (input.getKey(GLFW_KEY_A))
	{
		sprite.UpdateSprite(2, false, timer);
		sprite.setPosition(vec3(-1 * deltaTime, 0, 0));
	}

	if (input.getKey(GLFW_KEY_W))
	{
		sprite.UpdateSprite(3, false, timer);
		sprite.setPosition(vec3(0, 1 * deltaTime, 0));
	}

	if (input.getKey(GLFW_KEY_S))
	{
		sprite.UpdateSprite(5, false, timer);
		sprite.setPosition(vec3(0, -1 * deltaTime, 0));
	}
	if (timerSprite <= 10)
	{
		timerSprite = 0;
	}
	tilemap.CheckTileCollision(1, &sprite);

	//sprite2.UpdateSprite(static_cast<int>(timerSprite), false, timer);
	
	tilemap.Draw();
	sprite.draw();
	//sprite2.draw();
	
	//tile2.Draw();
}
