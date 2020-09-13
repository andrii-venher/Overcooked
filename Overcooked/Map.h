#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "TiledObject.h"
#include "Food.h"
#include "Utensils.h"
#include "Utility.h"
#include <list>
#include <algorithm>
#include <fstream>

using namespace sf;

class Map
{
	Sprite sprite;
	Texture texture;
	const int width = 11;
	const int height = 11;
	MapObjects** map;
	std::list<TiledObject*>& objects;
public:
	Map(Texture& texture, std::list<TiledObject*>& _objects);
	void draw(RenderWindow& rw);
	void update();
	Actions interact(int _x, int _y);
	Actions fabricate(int _x, int _y);
	MapObjects** getMap();
	MapObjects at(int _x, int _y);
	int getWidth();
	int getHeight();
};

