#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"
#include "Utensils.h"
#include "Utility.h"
#include "Map.h"
#include <list>
#include <iostream>

class Player : public TiledObject
{
	enum class States { LEFT, UP, RIGHT, DOWN, STAY, NEED_UPDATE };

	States state;
	float xSpeed;
	float ySpeed;
	TiledObject* inHands;
	std::list<TiledObject*>& objects;
public:
	Player(sf::Texture& texture, float _x, float _y, std::list<TiledObject*>& _objects);
	~Player();
	sf::Sprite getSprite();
	sf::Sprite getInHandsSprite();
	std::pair<int, int> getNextPosition();
	void update(float time, Map* map);
	void trackControls();
	void take();
	void put();
	bool isSomethingInHands();
	void draw(sf::RenderWindow& rw) override;
};

