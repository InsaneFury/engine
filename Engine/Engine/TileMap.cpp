#include "TileMap.h"
//Get poss rotoooo mi doler mucho cabeza.

namespace Engine
{
	TileMap::TileMap(Renderer* rend, float width, float height, const char* filename, float cantTilesX, float cantTilesY)
		: Shape(rend), mapWidth(width), mapHeight(height), cantX(cantTilesX), cantY(cantTilesY), lastPosX(0), lastPosY(0), xPos(0), yPos(0)
	{
		type = 'q';
		cantVertex = 12 * 12 * 4 * 3;
		cantUVvertex = 12 * 12 * 4 * 2;

		vertexes = new float[cantVertex];

		tileW = 2.0f;
		tileH = 2.0f;

		int column = 0;
		int row = 0;

		cout << "Creating tilemap Vertexes" << endl;
		for (int i = 0; i < cantVertex; i = i + 12)
		{
			// Coordenada 1
			vertexes[i] = -1.0f + tileW * column;
			vertexes[i + 1] = 1.0f - tileH * row;
			vertexes[i + 2] = 0.0f;

			// Coordenada 2
			vertexes[i + 3] = -1.0f + tileW * column;
			vertexes[i + 4] = (1.0f - tileH) - tileH * row;
			vertexes[i + 5] = 0.0f;

			// Coordenada 3
			vertexes[i + 6] = (-1.0f + tileW) + tileW * column;
			vertexes[i + 7] = (1.0f - tileH) - tileH * row;
			vertexes[i + 8] = 0.0f;

			// Coordenada 4
			vertexes[i + 9] = (-1.0f + tileW) + tileW * column;
			vertexes[i + 10] = 1.0f - tileH * row;
			vertexes[i + 11] = 0.0f;

			if (column >= 12 - 1)
			{
				column = 0;
				row++;
			}
			else
				column++;
		}

		mapIds = new vector<int>();
		bidimensionalIDs = vector<vector<int>>(height, vector<int>(width));
		tilesWithCollides = new vector<int>();
		tilesOnScreen = vector<vector<int>>(12, vector<int>(12));
		LoadMapIDs(filename);

		vertexUVTexture = new float[cantUVvertex];
		UpdateTilemap(lastPosX, lastPosY);

		SetTilemapVertex(vertexes, cantVertex);

		SetTextures(vertexUVTexture, cantUVvertex);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	TileMap::~TileMap()
	{
	}

	void TileMap::SetTextures(float* vertex, int cant)
	{
		textureUVBufferId = renderer->GenVertexBuffer(vertex, sizeof(float)* cant);
	}

	void TileMap::LoadTexture(const char* name)
	{
		header = TextureLoader::LoadBMP(name);
		textureBufferId = renderer->GenTextureBuffer(header.width, header.height, header.data);
	}

	void TileMap::Draw()
	{
		renderer->LoadIdentityMatrix();
		renderer->SetModel(model);

		if (material != NULL)
		{
			material->Bind();
			material->SetMatrixProperty("MVP", renderer->GetMVP());
			material->BindTexture("myTextureSampler", textureBufferId);
		}

		renderer->EnableAtribArray(0);
		renderer->EnableAtribArray(1);
		renderer->BindBuffer(vertexBufferID, 0);
		renderer->BindTextureBuffer(textureUVBufferId, 1);
		renderer->Draw(type, cantVertex);
		renderer->DisableBuffer(0);
		renderer->DisableBuffer(1);
	}

	void TileMap::LoadMapIDs(const char* file)
	{
		string buffer;
		ifstream tileFile(file);

		while (getline(tileFile, buffer, ','))
		{
			mapIds->push_back(stoi(buffer));
		}

		int count = 0;

		for (int i = 0; i < mapHeight; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				bidimensionalIDs[i][j] = mapIds->at(count);
				count++;
			}
		}

		mapIds->clear();
	}

	void TileMap::LoadUVs()
	{
		float textureW = 1 / cantX;
		float textureH = 1 / cantY;

		int idIndex = 0;

		for (int i = 0; i < cantUVvertex; i = i + 8)
		{
			// Coordenada 1
			vertexUVTexture[i] = 0.0f;
			vertexUVTexture[i + 1] = 1.0f;

			// Coordenada 2
			vertexUVTexture[i + 2] = 0.0f;
			vertexUVTexture[i + 3] = 1.0f - textureH;

			// Coordenada 3
			vertexUVTexture[i + 4] = textureW;
			vertexUVTexture[i + 5] = 1.0f - textureH;

			// Coordenada 4
			vertexUVTexture[i + 6] = textureW;
			vertexUVTexture[i + 7] = 1.0f;

			int row = 0;
			int column = mapIds->at(idIndex);

			while (column >= cantX)
			{
				column -= cantX;
				row++;
			}

			// Coordenada 1
			vertexUVTexture[i] += textureW * column;
			vertexUVTexture[i + 1] -= textureH * row;

			// Coordenada 2
			vertexUVTexture[i + 2] += textureW * column;
			vertexUVTexture[i + 3] -= textureH * row;

			// Coordenada 3
			vertexUVTexture[i + 4] += textureW * column;
			vertexUVTexture[i + 5] -= textureH * row;

			// Coordenada 4
			vertexUVTexture[i + 6] += textureW * column;
			vertexUVTexture[i + 7] -= textureH * row;

			idIndex++;
		}

		mapIds->clear();
	}

	void TileMap::SetTilemapVertex(float* vertex, int cant)
	{
		vertexBufferID = renderer->GenVertexBuffer(vertex, sizeof(float) * cant);
	}

	void TileMap::UpdateTilemap(float x, float y)
	{
		if (lastPosX + 1.95f <= x)
		{
			xPos++;
			this->SetTranslation(this->GetPosX() + 2.0f, this->GetPosY(), this->GetPosZ());
			lastPosX = x;
			lastPosY = y;
			cout << "Tilemap position is now " << GetPosX() << ", " << GetPosY() << endl;
			cout << "Player position is now " << x << ", " << y << endl;
		}

		for (int i = yPos; i < yPos + 12; i++)
		{
			for (int j = xPos; j < xPos + 12; j++)
			{
				mapIds->push_back(bidimensionalIDs.at(i).at(j));
			}
		}

		int aux = 0;

		for (int i = 0; i < tilesOnScreen.size(); i++)
		{
			for (int j = 0; j < tilesOnScreen.at(i).size(); j++)
			{
				tilesOnScreen[i][j] = mapIds->at(aux);
				aux++;
			}
		}

		LoadUVs();
		SetTextures(vertexUVTexture, cantUVvertex);
	}

	void TileMap::SetCollisionableTiles(int id)
	{
		tilesWithCollides->push_back(id);
	}

	bool TileMap::IsNextTileCollisionable(float playerX, float playerY, float size, Direction dir)
	{
		int row;
		int col;

		switch (dir)
		{
		case UP:
			row = (playerY - size - this->GetPosY()) / tileH;
			col = (playerX - this->GetPosX()) / tileW;
			if (row < 0) row *= -1;
			if (col < 0) col *= -1;
			row--;
			break;
		case DOWN:
			row = (playerY - this->GetPosY()) / tileH;
			col = (playerX - this->GetPosX()) / tileW;
			if (row < 0) row *= -1;
			if (col < 0) col *= -1;
			row++;
			break;
		case RIGHT:
			row = (playerY - size - this->GetPosY()) / tileH;
			col = (playerX - this->GetPosX()) / tileW;
			if (row < 0) row *= -1;
			if (col < 0) col *= -1;
			col++;
			break;
		case LEFT:
			row = (playerY - this->GetPosY()) / tileH;
			col = (playerX + size - this->GetPosX()) / tileW;
			if (row < 0) row *= -1;
			if (col < 0) col *= -1;
			col--;
			break;
		}

		int id = tilesOnScreen.at(row).at(col);

		for (int i = 0; i < tilesWithCollides->size(); i++)
		{
			if (id == tilesWithCollides->at(i))
			{
				return true;
			}
		}

		return false;
	}

	void TileMap::SetLastPositions(float x, float y)
	{
		lastPosX = x;
		lastPosY = y;
	}
}