#pragma once
#include "Renderer.h"
#include "Sprite.h"
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Renderer.h"
using namespace std;
namespace Engine
{

class DLLEXPORT TileMap
{
private:
	vector<Sprite> tiles;
	vector<int> csvData;
	vector<vec2> ID;
public:
	TileMap();
	void Set(Renderer _render, Color spriteColor, const char* path, vec2 cantUV,vec2 cantTile, vec2 sizeTile, const char* pathCSV);
	void Draw();
	void ReadCSV(const char* path);
	void CheckTileCollision(int id, Sprite* player);
};

}
