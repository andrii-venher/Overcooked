#pragma once
#include "TiledObject.h"
#include "Food.h"
#include <list>

class Utensils : public TiledObject
{
protected:
	std::list<Food*> filling;
	int readyTimer = 0;
	bool isOnStove = false;
	RectangleShape readyBar;
public:
	Utensils(const Utensils& food);
	Utensils(Texture& texture, int tileX, int tileY);
	Utensils(Texture& texture, float _x, float _y, int tileX, int tileY);
	bool add(TiledObject* obj);
	int getFillingSize();
	void setStove(bool _isOnStove);
	void update(float time);
	void draw(RenderWindow& rw) override;
};

class Pan : public Utensils
{
public:
	Pan(Texture& texture);
	Pan(Texture& texture, float _x, float _y);
	TiledObject* clone() override;
};

