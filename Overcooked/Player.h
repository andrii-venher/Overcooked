#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"

using namespace sf;

class Player : public TiledObject
{
	TiledObject* inHands;
	enum class States { LEFT, UP, RIGHT, DOWN, STAY };
	States state;
	float xSpeed;
	float ySpeed;
public:
	Player(Texture& texture, IntRect _tileRect, float _x, float _y);
	void update(float time);
	void trackControls();
	Sprite getSprite();
	Sprite getInHands();
};

