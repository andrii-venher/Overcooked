#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

using namespace sf;

class Map
{
	Sprite sprite;
	const int width;
	const int height;

	enum class MapObjects { PLAYER, TABLE, FLOOR, CHECKOUT };

	MapObjects** tileMap;
public:
	Map(Texture& texture);
	void repaint(RenderWindow& window);
};

