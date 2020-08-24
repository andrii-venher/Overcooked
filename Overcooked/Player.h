#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"
#include <list>
#include <iostream>

using namespace sf;

class Player : public TiledObject
{
	TiledObject* inHands;
	enum class States { LEFT, UP, RIGHT, DOWN, STAY, NEEDS_UPDATE };
	States state;
	float xSpeed;
	float ySpeed;
	std::list<TiledObject*>& objects;
public:
	Player(Texture& texture, float _x, float _y, int tileX, int tileY, std::list<TiledObject*>& _objects);
	void update(float time);
	void trackControls();
	Sprite getSprite();
	bool isSomethingInHands();
	Sprite getInHandsSprite();
	void takeIntoHands();
	void putFromHands();
};

