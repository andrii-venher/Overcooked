#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameSettings.h"

using namespace sf;

enum class Rotations { LEFT, UP, RIGHT, DOWN };

class TiledObject
{
protected:
	Sprite sprite;
	float x;
	float y;
	IntRect tileRect;
public:
	TiledObject();
	TiledObject(Texture& texture, float _x, float _y, int tileX, int tileY);
	Sprite getSprite();
	void setPosition(float _x, float _y);
	IntRect getTileRect();
	Rotations getRotation();
};

