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
	const int readyTime = 1000;
	const int maxCapacity = 3;
	virtual void switchTexture() = 0;
	virtual void setStandartTexture() = 0;
	bool isFoodEqualInFilling();
public:
	Utensils(const Utensils& food);
	Utensils(Texture& texture, int tileX, int tileY);
	Utensils(Texture& texture, float _x, float _y, int tileX, int tileY);
	bool add(TiledObject* obj);
	int getCapacity();
	void isOnStrove(bool _isOnStove);
	void update(float time);
	void draw(RenderWindow& rw) override;
};

class Pan : public Utensils
{
	void switchTexture() override;
	void setStandartTexture() override;
public:
	Pan(Texture& texture);
	Pan(Texture& texture, float _x, float _y);
	TiledObject* clone() override;
};

