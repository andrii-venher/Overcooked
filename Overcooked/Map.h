#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Map
{
	Sprite sprite;
	const int width;
	const int height;

	enum class MapObjects { PLAYER, TABLE, CHECKOUT };

	MapObjects** tileMap;
public:
	Map(Texture& texture);
	void repaint(RenderWindow& window);
};

