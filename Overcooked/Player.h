#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"
#include "Utensils.h"
#include "Utility.h"
#include <list>
#include <iostream>

class Player : public TiledObject
{
	TiledObject* inHands;
	enum class States { LEFT, UP, RIGHT, DOWN, STAY, NEEDS_UPDATE };
	States state;
	float xSpeed;
	float ySpeed;
	std::list<TiledObject*>& objects;
public:
	Player(sf::Texture& texture, float _x, float _y, std::list<TiledObject*>& _objects);
	void update(float time, MapObjects** map);
	void trackControls();
	sf::Sprite getSprite();
	bool isSomethingInHands();
	sf::Sprite getInHandsSprite();
	void take();
	void put();
	std::pair<int, int> getNextPosition();
	void draw(sf::RenderWindow& rw) override;
};

