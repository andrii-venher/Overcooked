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
			if (i == 0 && j == 1)
				tileMap[i][j] = MapObjects::STOVE;
			else if (i == 0 && j == 7)
				tileMap[i][j] = MapObjects::CUTTING_BOARD;
			else if (i == 0 && j == 2)
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
				sprite.setTextureRect(IntRect(1 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if (tileMap[i][j] == MapObjects::TOMATO_DISPENSER)
				sprite.setTextureRect(IntRect(0 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(tileMap[i][j] == MapObjects::CUTTING_BOARD)
				sprite.setTextureRect(IntRect(4 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			else if(tileMap[i][j] == MapObjects::STOVE)
				sprite.setTextureRect(IntRect(5 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
				
			sprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
			rw.draw(sprite);
		}
	}
}

void Map::update()
{
	for(auto obj : objects)
	{
		switch (obj->getType())
		{
		case ObjectTypes::UTENSILS:
		{
			CookingUtensils* utenObj = (CookingUtensils*)obj;
			Vector2f pos = convertPosition(utenObj);
			if (tileMap[(int)pos.y][(int)pos.x] == MapObjects::STOVE)
			{
				utenObj->isOnStrove(true);
				//std::cout << "TRUE\n";
			}
			else
			{
				utenObj->isOnStrove(false);
				//std::cout << "FALSE\n";
			}
		}
		default:
			break;
		}
	}
}

Actions Map::interact(int _x, int _y)
{
	_x /= TILE_SIZE;
	_y /= TILE_SIZE;
	//std::cout << _x << " " << _y << "\n";
	if (tileMap[_y][_x] == MapObjects::TOMATO_DISPENSER)
	{
		objects.push_back(new Tomato(texture, _x * TILE_SIZE + TILE_SIZE / 2, _y * TILE_SIZE  + TILE_SIZE / 2));
		return Actions::TAKE;
	}
	return Actions::WAIT;
}

Actions Map::fabricate(int _x, int _y)
{
	bool isOnBoard = false;
	TiledObject* object = nullptr;
	_x /= TILE_SIZE;
	_y /= TILE_SIZE;

	//std::cout << _x << " " << _y << "\n";

	for (auto obj : objects)
	{
		if (obj->getSprite().getPosition() == Vector2f(_x * TILE_SIZE + TILE_SIZE / 2, _y * TILE_SIZE + TILE_SIZE / 2))
		{
			object = obj;
			break;
		}
	}

	if (object)
	{
		if (tileMap[_y][_x] == MapObjects::CUTTING_BOARD && object->getType() == ObjectTypes::FOOD)
		{
			Food* foodObj = (Food*)object;
			foodObj->cut();
		}
		else if (tileMap[_y][_x] == MapObjects::STOVE && object->getType() == ObjectTypes::UTENSILS)
		{

			CookingUtensils* utenObj = (CookingUtensils*)object;
			switch (utenObj->getCapacity())
			{
			case 0:
				std::cout << "empty!\n";
				break;
			case 1:
				std::cout << "1 filling!\n";
				break;
			case 2:
				std::cout << "2 filling!\n";
				break;
			case 3:
				std::cout << "3 filling!\n";
				break;
			default:
				break;
			}
			//Vector2f pos = utenObj->getSprite().getPosition();
			//int _x = pos.x / TILE_SIZE;
			//int _y = pos.y / TILE_SIZE;
			
			//std::cout << "Successful cooking!\n";
		}
	}

	//std::cout << _x << " " << _y << "\n";
	
	return Actions::WAIT;
}

MapObjects** Map::getMap()
{
	return tileMap;
}
