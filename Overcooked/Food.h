#pragma once
#include "TiledObject.h"

enum class FoodTypes { TOMATO, MUSHROOM, ONION };

class Food : public TiledObject
{
protected:
	bool cooked = false;
	const int cutsNeeded = 3;
	unsigned int cutCounter = 0;
	FoodTypes fType;
	sf::RectangleShape cutBar;

	virtual void changeTexture() = 0;
public:
	Food(const Food& food);
	Food(sf::Texture& texture, int tileX, int tileY);
	Food(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	void cut();
	bool isCut();
	void setCooked();
	bool isCooked();
	FoodTypes getFoodType();
	void draw(sf::RenderWindow& rw) override;
};

class Tomato : public Food
{
	void changeTexture() override;
public:
	Tomato(sf::Texture& texture);
	Tomato(sf::Texture& texture, float _x, float _y);
};

class Mushroom : public Food
{
	void changeTexture() override;
public:
	Mushroom(sf::Texture& texture);
	Mushroom(sf::Texture& texture, float _x, float _y);
};

class Onion : public Food
{
	void changeTexture() override;
public:
	Onion(sf::Texture& texture);
	Onion(sf::Texture& texture, float _x, float _y);
};
