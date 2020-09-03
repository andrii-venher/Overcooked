#pragma once
#include "TiledObject.h"
#include <unordered_map>

enum class FoodTypes { TOMATO };

class Food : public TiledObject
{
protected:
	unsigned int cutCounter = 0;
	virtual void changeTexture() = 0;
public:
	Food(const Food& food);
	Food(Texture& texture, int tileX, int tileY);
	Food(Texture& texture, float _x, float _y, int tileX, int tileY);
	void cut();
	bool isCut();
};

class Tomato : public Food
{
	void changeTexture() override;
public:
	Tomato(Texture& texture);
	Tomato(Texture& texture, float _x, float _y);
	TiledObject* clone() override;
};

class FoodFactory
{
	std::unordered_map<FoodTypes, TiledObject*> prototypes;
public:
	FoodFactory(Texture& t);
	~FoodFactory();
	TiledObject* create(FoodTypes type, float _x, float _y);
};