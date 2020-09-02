#pragma once
#include "TiledObject.h"
class Food : public TiledObject
{
public:
	Food(Texture& texture, float _x, float _y, int tileX, int tileY);
};

class Tomato : public Food
{
public:
	Tomato(Texture& texture, float _x, float _y);
};

