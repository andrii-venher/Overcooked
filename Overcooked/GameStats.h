#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <iostream>

class StatObject
{
	sf::Sprite sprite;
	sf::Font font;
	sf::Text text;
public:
	StatObject(sf::Texture& _texture, sf::Font& _font, int tileX, int tileY, float _x, float _y);
	void setText(std::string _text);
	void draw(sf::RenderWindow& rw);
};

class GameStats
{
	sf::Font font;
	StatObject* tips;
	StatObject* timer;
	float time = 0.0;
	sf::RectangleShape background;
public:
	GameStats(sf::Texture& _texture, float _x, float _y);
	void update(float _time, int _tips);
	void draw(sf::RenderWindow& rw);
};

