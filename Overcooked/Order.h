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
	RectangleShape timerBar;
	int height = TILE_SIZE + 6;
	int width = TILE_SIZE * 3 + 6;
	RectangleShape outer;
	RectangleShape inner;
	int tips = 4;
	bool completed = false;
public:
	Order(Texture& t);
	bool isValid();
	void complete();
	bool isCompleted();
	void update(float time);
	void draw(RenderWindow& rw);
	void setPosition(float _x, float _y);
	float getHeight();
	float getWidth();
	std::list<Food*> getList();
	Vector2f getPosition();
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
	void draw(RenderWindow& rw);
	void setPosition(float _x, float _y);
	std::list<Order*> getOrders();
	int getTips();
};

class RandomOrderFactory
{
	Texture& texture;
public:
	RandomOrderFactory(Texture& _texture);
	Order* create();
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


