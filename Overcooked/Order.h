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
	int orderTime = 80000;
	float timer = 0;
	int height = TILE_SIZE + 6;
	int width = TILE_SIZE * 3 + 6;
	int tips = 4;
	bool completed = false;
	std::list<Food*> foodList;
	sf::RectangleShape timerBar;
	sf::RectangleShape outer;
	sf::RectangleShape inner;
public:
	Order(sf::Texture& t);
	~Order();
	float getHeight();
	float getWidth();
	int getOrderTime();
	int getTips();
	sf::Vector2f getPosition();
	bool isValid();
	bool isCompleted();
	void complete();
	void setPosition(float _x, float _y);
	void update(float time);
	std::list<Food*> getList();
	void draw(sf::RenderWindow& rw);
};

class OrderQueue
{
	float x = 0;
	float y = 0;
	int totalTips = 0;
	std::list<Order*> queue;
	void resetPosition(Order* order);
public:
	~OrderQueue();
	int getTips();
	void setPosition(float _x, float _y);
	void add(Order* order);
	void update(float time);
	std::list<Order*> getOrders();
	void draw(sf::RenderWindow& rw);
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


