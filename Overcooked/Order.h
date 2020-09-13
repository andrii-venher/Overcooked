#pragma once
#include <SFML/Graphics.hpp>
#include "Food.h"
#include "Utensils.h"

class Order
{
	void resetFieldsPosition();
protected:
	float x = 0;
	float y = 0;
	std::list<Food*> foodList;
	float timer = 0;
	int orderTime = 10000000;
	RectangleShape timerBar;
	int height = TILE_SIZE + 6;
	int width = TILE_SIZE * 3 + 6;
	RectangleShape outer;
	RectangleShape inner;
public:
	Order(Texture& t);
	bool isValid();
	void complete();
	void update(float time);
	void draw(RenderWindow& rw);
	void setPosition(float _x, float _y);
	float getHeight();
	float getWidth();
	std::list<Food*> getList();
	Vector2f getPosition();
};

class OrderQueue
{
	float x = 0;
	float y = 0;
	std::list<Order*> queue;
	void resetPosition(Order* order);
public:
	void add(Order* order);
	void update(float time);
	void draw(RenderWindow& rw);
	void setPosition(float _x, float _y);
	std::list<Order*> getOrders();
};

class TomatoSoupOrder : public Order
{
public:
	TomatoSoupOrder(Texture& t);
};

class MushroomSoupOrder : public Order
{
public:
	MushroomSoupOrder(Texture& t);
};

class OnionSoupOrder : public Order
{
public:
	OnionSoupOrder(Texture& t);
};


