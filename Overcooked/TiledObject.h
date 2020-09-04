#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameSettings.h"

using namespace sf;

enum class ObjectTypes { PLAYER, FOOD, UTENSILS };

class TiledObject
{
protected:
	Sprite sprite;
	float x;
	float y;
	IntRect tileRect;
	ObjectTypes type;
public:
	TiledObject(const TiledObject& obj);
	TiledObject(Texture& texture, int tileX, int tileY);
	TiledObject(Texture& texture, float _x, float _y, int tileX, int tileY);
	Sprite getSprite();
	void setPosition(float _x, float _y);
	IntRect getTileRect();
	Rotations getRotation();
	virtual void draw(RenderWindow& rw);
	virtual TiledObject* clone() = 0;
	ObjectTypes getType();
};

