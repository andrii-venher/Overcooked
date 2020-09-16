#include "Map.h"

Map::Map(sf::Texture& _texture, std::list<TiledObject*>& _objects) : objects(_objects)
{
	sprite.setTexture(_texture);
	texture = _texture;

	map = new MapObjects * [height];

	std::ifstream file("Levels/level1.map");

	for (int i = 0; i < height; i++)
	{
		map[i] = new MapObjects[width];
	}
	char ch;
	int i = 0;
	int j = 0;
	while (!file.eof())
	{
		file.read(&ch, 1);
		if (file.eof())
			break;
		switch (ch)
		{
		case '1':
			map[i][j] = MapObjects::TABLE;
			break;
		case '0':
			map[i][j] = MapObjects::FLOOR;
			break;
		case 'c':
			map[i][j] = MapObjects::CHECKOUT;
			break;
		case 'b':
			map[i][j] = MapObjects::CUTTING_BOARD;
			break;
		case 's':
			map[i][j] = MapObjects::STOVE;
			break;
		case 't':
			map[i][j] = MapObjects::TOMATO_DISPENSER;
			break;
		case 'm':
			map[i][j] = MapObjects::MUSHROOM_DISPENCER;
			break;
		case 'o':
			map[i][j] = MapObjects::ONION_DISPENCER;
			break;	
		case 'T':
			map[i][j] = MapObjects::TRASH;
			break;
		case '\n':
			i++;
			j = 0;
			continue;
		default:
			break;
		}
		j++;
	}
	file.close();
}

void Map::draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == MapObjects::FLOOR)
				sprite.setTextureRect(sf::IntRect(1 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (map[i][j] == MapObjects::TABLE)
				sprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (map[i][j] == MapObjects::CHECKOUT)
				sprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (map[i][j] == MapObjects::CUTTING_BOARD)
				sprite.setTextureRect(sf::IntRect(4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(map[i][j] == MapObjects::STOVE)
				sprite.setTextureRect(sf::IntRect(5 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(map[i][j] == MapObjects::TRASH)
				sprite.setTextureRect(sf::IntRect(6 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (map[i][j] == MapObjects::TOMATO_DISPENSER)
				sprite.setTextureRect(sf::IntRect(0 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(map[i][j] == MapObjects::MUSHROOM_DISPENCER)
				sprite.setTextureRect(sf::IntRect(0 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (map[i][j] == MapObjects::ONION_DISPENCER)
				sprite.setTextureRect(sf::IntRect(0 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
				
			sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
			rw.draw(sprite);
		}
	}
}

MapObjects** Map::getMap()
{
	return map;
}

MapObjects Map::at(int _x, int _y)
{
	return map[_y][_x];
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}
