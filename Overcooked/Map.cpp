#include "Map.h"

Map::Map(Texture& texture) : width(10), height(10)
{
	sprite.setTexture(texture);

	tileMap = new MapObjects * [width];

	for (int i = 0; i < height; i++)
	{
		tileMap[i] = new MapObjects[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 && j == 5)
				tileMap[i][j] = MapObjects::CHECKOUT;
			else if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
				tileMap[i][j] = MapObjects::TABLE;
			else
				tileMap[i][j] = MapObjects::FLOOR;
		}
	}
}

void Map::repaint(RenderWindow& window)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tileMap[i][j] == MapObjects::TABLE)
				sprite.setTextureRect(IntRect(64, 0, TILE_SIZE, TILE_SIZE));
			else if (tileMap[i][j] == MapObjects::CHECKOUT)
				sprite.setTextureRect(IntRect(96, 0, TILE_SIZE, TILE_SIZE));
			else if(tileMap[i][j] == MapObjects::FLOOR)
				sprite.setTextureRect(IntRect(128, 0, TILE_SIZE, TILE_SIZE));
			
			sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
			window.draw(sprite);
		}
	}
}
