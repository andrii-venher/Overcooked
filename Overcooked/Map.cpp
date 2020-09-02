#include "Map.h"

Map::Map(Texture& _texture, std::list<TiledObject*>& _objects) : width(10), height(10), objects(_objects)
{
	sprite.setTexture(_texture);
	texture = _texture;

	tileMap = new MapObjects * [width];

	for (int i = 0; i < height; i++)
	{
		tileMap[i] = new MapObjects[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 && j == 2)
				tileMap[i][j] = MapObjects::TOMATO_DISPENSER;
			else if (i == 0 && j == 5)
				tileMap[i][j] = MapObjects::CHECKOUT;
			else if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
				tileMap[i][j] = MapObjects::TABLE;
			else
				tileMap[i][j] = MapObjects::FLOOR;
		}
	}
}

void Map::draw(RenderWindow& rw)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tileMap[i][j] == MapObjects::TABLE)
				sprite.setTextureRect(IntRect(2 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (tileMap[i][j] == MapObjects::CHECKOUT)
				sprite.setTextureRect(IntRect(3 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(tileMap[i][j] == MapObjects::FLOOR)
				sprite.setTextureRect(IntRect(4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (tileMap[i][j] == MapObjects::TOMATO_DISPENSER)
			{
				/*static Tomato* tomato = new Tomato(texture, j * TILE_SIZE + 16, i * TILE_SIZE + 16);
				if (tomato == nullptr)
				{
					tomato = new Tomato(texture, j * TILE_SIZE + 16, i * TILE_SIZE + 16);
					objects.push_back(tomato);
				}*/
				/*if (std::find(std::begin(objects), std::end(objects), new Tomato(texture, j * TILE_SIZE + 16, i * TILE_SIZE + 16)) == std::end(objects))
				{
					objects.push_back(new Tomato(texture, j * TILE_SIZE + 16, i * TILE_SIZE + 16));
					std::cout << "new tomato\n";
				}*/
					
				sprite.setTextureRect(IntRect(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			}
				
			
			sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
			rw.draw(sprite);
		}
	}
}

Actions Map::interact(int _x, int _y)
{
	_x /= TILE_SIZE;
	_y /= TILE_SIZE;
	std::cout << _x << " " << _y << "\n";
	if (tileMap[_y][_x] == MapObjects::TOMATO_DISPENSER)
	{
		objects.push_back(new Tomato(texture, _x * TILE_SIZE + TILE_SIZE / 2, _y * TILE_SIZE  + TILE_SIZE / 2));
		return Actions::TAKE;
	}
	return Actions::WAIT;
}
