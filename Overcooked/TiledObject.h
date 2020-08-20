#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TiledObject
{
protected:
	Sprite sprite;
	float x;
	float y;
	IntRect tileRect;
public:
	TiledObject(Texture& texture, float _x, float _y, IntRect _tileRect);
	Sprite getSprite();
	void setPosition(float _x, float _y);
	IntRect getTileRect();
};

