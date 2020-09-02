#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "TiledObject.h"
#include "Food.h"
#include <list>
#include <algorithm>

using namespace sf;

class Map
{
	Sprite sprite;
	Texture texture;
	const int width;
	const int height;

	enum class MapObjects { PLAYER, TABLE, FLOOR, CHECKOUT, TOMATO_DISPENSER };

	MapObjects** tileMap;
	std::list<TiledObject*>& objects;
public:
	Map(Texture& texture, std::list<TiledObject*>& _objects);
	void draw(RenderWindow& rw);
	Actions interact(int _x, int _y);
};

