#ifndef TILEMAP_H
#define TILEMAP_H

#include "Entity2D.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

namespace Engine
{

	enum Direction
	{
		UP, DOWN, RIGHT, LEFT
	};

	class TileMap : public Entity2D
	{
	private:
		int mapWidth;
		int mapHeight;
		int cantUVvertex;
		float cantX;
		float cantY;
		float tileW;
		float tileH;
		float xPos;
		float yPos;
		float lastPosY;
		float lastPosX;
		vector<int>* mapIds;
		vector<int>* tilesWithCollides;
		vector<vector<int>> bidimensionalIDs;
		vector<vector<int>> tilesOnScreen;
	public:
		TileMap(Renderer* rend, float width, float height, const char* filename, float cantTilesX, float cantTilesY);
		~TileMap();
		void draw();
		void SetTextures(float* vertex, int cant);
		void LoadTexture(const char* name);
		void LoadUVs();
		void LoadMapIDs(const char* file);
		void SetTilemapVertex(float* vertex, int cant);
		void UpdateTilemap(float x, float y);
		void SetCollisionableTiles(int id);
		bool IsNextTileCollisionable(float posX, float posY, float size, Direction dir);
		void SetLastPositions(float x, float y);
	};
}


#endif // !TILEMAP_H


