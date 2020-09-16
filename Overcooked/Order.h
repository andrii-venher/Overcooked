#pragma once
#include <SFML/Graphics.hpp>
#include "Food.h"
#include "Utensils.h"
#include <ctime>

class Order
{
	void resetFieldsPosition();
protected:
	float x = 0;
	float y = 0;
	std::list<Food*> foodList;
	float timer = 0;
	int orderTime = 80000;
	sf::RectangleShape timerBar;
	int height = TILE_SIZE + 6;
	int width = TILE_SIZE * 3 + 6;
	sf::RectangleShape outer;
	sf::RectangleShape inner;
	int tips = 4;
	bool completed = false;
public:
	Order(sf::Texture& t);
	bool isValid();
	void complete();
	bool isCompleted();
	void update(float time);
	void draw(sf::RenderWindow& rw);
	void setPosition(float _x, float _y);
	float getHeight();
	float getWidth();
	std::list<Food*> getList();
	sf::Vector2f getPosition();
	int getOrderTime();
	int getTips();
};

class OrderQueue
{
	float x = 0;
	float y = 0;
	int totalTips = 0;
	std::list<Order*> queue;
	void resetPosition(Order* order);
public:
	void add(Order* order);
	void update(float time);
	void draw(sf::RenderWindow& rw);
	void setPosition(float _x, float _y);
	std::list<Order*> getOrders();
	int getTips();
};

class RandomOrderFactory
{
	sf::Texture& texture;
public:
	RandomOrderFactory(sf::Texture& _texture);
	Order* create();
};

class TomatoSoupOrder : public Order
{
public:
	TomatoSoupOrder(sf::Texture& t);
};

class MushroomSoupOrder : public Order
{
public:
	MushroomSoupOrder(sf::Texture& t);
};

class OnionSoupOrder : public Order
{
public:
	OnionSoupOrder(sf::Texture& t);
};


