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

class Map
{
	sf::Sprite sprite;
	sf::Texture texture;
	const int width = 11;
	const int height = 11;
	MapObjects** map;
	std::list<TiledObject*>& objects;
public:
	Map(sf::Texture& texture, std::list<TiledObject*>& _objects);
	void draw(sf::RenderWindow& rw);
	MapObjects** getMap();
	MapObjects at(int _x, int _y);
	int getWidth();
	int getHeight();
};

