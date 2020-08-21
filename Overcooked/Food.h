#pragma once
#include "TiledObject.h"
class Food : public TiledObject
{
public:
	Food(Texture& texture, float _x, float _y, IntRect _tileRect);
};

