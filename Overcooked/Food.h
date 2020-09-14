#pragma once
#include "TiledObject.h"

enum class FoodTypes { TOMATO, MUSHROOM, ONION };

class Food : public TiledObject
{
protected:
	unsigned int cutCounter = 0;
	virtual void changeTexture() = 0;
	FoodTypes fType;
	RectangleShape cutBar;
	const int cutsNeeded = 3;
	bool cooked = false;
public:
	Food(const Food& food);
	Food(Texture& texture, int tileX, int tileY);
	Food(Texture& texture, float _x, float _y, int tileX, int tileY);
	void cut();
	bool isCut();
	void setCooked();
	bool isCooked();
	FoodTypes getFoodType();
	void draw(RenderWindow& rw) override;
};

class Tomato : public Food
{
	void changeTexture() override;
public:
	Tomato(Texture& texture);
	Tomato(Texture& texture, float _x, float _y);
};

class Mushroom : public Food
{
	void changeTexture() override;
public:
	Mushroom(Texture& texture);
	Mushroom(Texture& texture, float _x, float _y);
};

class Onion : public Food
{
	void changeTexture() override;
public:
	Onion(Texture& texture);
	Onion(Texture& texture, float _x, float _y);
};
