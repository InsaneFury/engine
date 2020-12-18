#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace Engine;
using namespace std;
TileMap::TileMap()
{
	
		
}

void TileMap::Set(Renderer _render, Color spriteColor, const char* path, vec2 cantUV,vec2 cantTile, vec2 sizeTile, const char* pathCSV)
{
	ReadCSV(pathCSV);
	int add = 0;
	for (int y = cantUV.y; y > 0; y--)
	{
	for(int x = 0 ; x< cantUV.x; x++)
	{
	
			ID.push_back(vec2(x, y-1));
		
	}
	}
	for (int y = 0; y < cantTile.x; y++)
	{
		for (int x = 0; x < cantTile.x; x++)
		{
			Sprite tile;
			tile.set(_render, spriteColor);
			tile.SetMaterial1(path, GL_RGB, true, GL_NEAREST);

			//cout << "TileX " << tile.size().x << "TileY " << tile.size().y << endl;

			tile.setPosition(vec3(-0.9 + x * 0.2f,0.9 + -y * 0.2f, 0.f));

			cout <<"Tile Position Start: "<< tile.getPosition().x << " " << tile.getPosition().y << endl;

			tile.SetAnimation(cantUV, 0.0f, ID[csvData[x + add]]);
			tile.Scale(vec3(1.0f, 1.0f, 1.0f));
			tile.id = csvData[x + add];
			tiles.push_back(tile);

		}
		add += cantTile.x;
		
	}
}

void TileMap::ReadCSV(const char* path)
{
	ifstream csv(path);
	if (!csv.is_open())
		cout << "ERROR: File Open" << endl;
	else
		cout << "File Open" << endl;

	string data;
	int uvData;

	while (csv.good())
	{
		getline(csv, data, ',');
		uvData = stoi(data); 
		csvData.push_back(uvData);
	}
}

void TileMap::Draw()
{
	for (int i = 0; i < tiles.size(); i++)
		tiles[i].draw();
}

void TileMap::CheckTileCollision(int id, Sprite* player)
{	
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].id == id)
		{
			
			//player->libre = player->BoxCollider.CollisionDetection(player->getPosition(), tiles[i].getPosition()+vec3(100.f,100.f, 0.f), player->size(),vec2(40.f,40.f));
			vec3 tileCenter = vec3(tiles[i].size().x, tiles[i].size().y, 0.0f) /2.0f;
			vec3 desfase = vec3(tiles[i].getPosition().x - tiles[i].size().x*2, tiles[i].getPosition().y - tiles[i].size().y*2, 0.0f);

			if(player->BoxCollider.CollisionDetection(player->getPosition(), desfase, player->size(), tiles[i].size()))
			{
				cout << tiles[i].getPosition().x <<" : "<< tiles[i].getPosition().y << endl;
				player->model = player->oldModel;
				player->position = player->oldPosition;
			}
		}
	}
}