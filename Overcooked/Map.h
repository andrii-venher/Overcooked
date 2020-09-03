#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "TiledObject.h"
#include "Food.h"
#include "Utensils.h"
#include "Utility.h"
#include <list>
#include <algorithm>

using namespace sf;

class Map
{
	Sprite sprite;
	Texture texture;
	const int width;
	const int height;
	MapObjects** tileMap;
	std::list<TiledObject*>& objects;
public:
	Map(Texture& texture, std::list<TiledObject*>& _objects);
	void draw(RenderWindow& rw);
	void update();
	Actions interact(int _x, int _y);
	Actions fabricate(int _x, int _y);
	MapObjects** getMap();
};

