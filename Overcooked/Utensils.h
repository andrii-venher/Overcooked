#pragma once
#include "TiledObject.h"
#include "Food.h"
#include <list>

enum class UtensilType { COOKING, DISHES };

class Utensil : public TiledObject
{
protected:
	std::list<Food*> filling;
	const int maxCapacity = 3;
	UtensilType utensilType;
	virtual void switchTexture() = 0;
	virtual void setStandartTexture() = 0;
	bool isFoodEqualInFilling();
public:
	Utensil(const Utensil& utensils);
	Utensil(Texture& texture, int tileX, int tileY);
	Utensil(Texture& texture, float _x, float _y, int tileX, int tileY);
	bool add(TiledObject* obj);
	int getCapacity();
	UtensilType getUtensilType();
};

class CookingUtensils : public Utensil
{
protected:
	int readyTimer = 0;
	bool isOnStove = false;
	RectangleShape readyBar;
	const int readyTime = 1000;
public:
	CookingUtensils(const CookingUtensils& cookingUtensils);
	CookingUtensils(Texture& texture, int tileX, int tileY);
	CookingUtensils(Texture& texture, float _x, float _y, int tileX, int tileY);
	void isOnStrove(bool _isOnStove);
	void update(float time);
	void draw(RenderWindow& rw) override;
};

class Plate : public Utensil
{
	void switchTexture() override;
	void setStandartTexture() override;
public:
	Plate(const Plate& plate);
	Plate(Texture& texture);
	Plate(Texture& texture, float _x, float _y);
};

class Pan : public CookingUtensils
{
	void switchTexture() override;
	void setStandartTexture() override;
public:
	Pan(Texture& texture);
	Pan(Texture& texture, float _x, float _y);
	TiledObject* clone() override;
};

