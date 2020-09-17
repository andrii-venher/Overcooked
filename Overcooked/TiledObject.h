#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameSettings.h"

enum class ObjectTypes { PLAYER, FOOD, UTENSIL };

class TiledObject
{
protected:
	sf::Sprite sprite;
	float x;
	float y;
	sf::IntRect tileRect;
	ObjectTypes type;
public:
	TiledObject(sf::Texture& texture, int tileX, int tileY);
	TiledObject(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	sf::Sprite getSprite();
	Rotations getRotation();
	sf::IntRect getTileRect();
	void setPosition(float _x, float _y);
	void setScale(float _factorX, float _factorY);
	virtual void draw(sf::RenderWindow& rw);
	ObjectTypes getType();
};

