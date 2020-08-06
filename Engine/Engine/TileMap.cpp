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
	for (int x = 0; x < cantTile.x; x++)
	{
		for (int y = 0; y < cantTile.y; y++)
		{
			
			Sprite tile;
			tile.set(_render, spriteColor);
			tile.SetMaterial1(path, GL_RGB, true, GL_NEAREST);
			tile.setPosition(vec3(-1 + y * sizeTile.x /200,1 + -x * sizeTile.y /200, 0.f));
			//tile.setPosition(vec3(x * sizeTile.x, y * sizeTile.y, 0.f));
			tile.SetAnimation(cantUV, 0.0f, ID[csvData[y + add]]);
			tile.Scale(vec3(1.0f, 1.0f, 1.0f));
			tile.id = csvData[y + add];
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

void TileMap::GetTile(int id, Sprite* player)
{	
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].id == id)
		{
			//player->libre = player->BoxCollider.CollisionDetection(player->getPosition(), tiles[i].getPosition()+vec3(100.f,100.f, 0.f), player->size(),vec2(40.f,40.f));
			vec3 tileCenter = vec3(tiles[i].size().x, tiles[i].size().y, 0.0f) /2.0f;
			if(! player->BoxCollider.CollisionDetection(player->getPosition(), tiles[i].getPosition() + tileCenter, player->size(), tiles[i].size()))
			{
				player->model = player->oldModel;
				player->position = player->oldPosition;
			}
		}
	}
}