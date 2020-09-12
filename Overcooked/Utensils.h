#pragma once
#include "TiledObject.h"
#include "Food.h"
#include <list>

enum class UtensilType { COOKING, PLATE };

class Utensil : public TiledObject
{
protected:
	std::list<Food*> filling;
	const int maxCapacity = 3;
	UtensilType utensilType;
	virtual void changeTexture() = 0;
	virtual void setStandartTexture() = 0;
	bool isFoodEqualInFilling();
public:
	Utensil(const Utensil& utensils);
	Utensil(Texture& texture, int tileX, int tileY);
	Utensil(Texture& texture, float _x, float _y, int tileX, int tileY);
	virtual bool add(TiledObject* obj) = 0;
	int getCapacity();
	void moveToUtensil(Utensil* utenObj);
	UtensilType getUtensilType();
};

class CookingUtensil : public Utensil
{
protected:
	int readyTimer = 0;
	bool isOnStove = false;
	RectangleShape readyBar;
	const int readyTime = 1000;
public:
	CookingUtensil(const CookingUtensil& cookingUtensils);
	CookingUtensil(Texture& texture, int tileX, int tileY);
	CookingUtensil(Texture& texture, float _x, float _y, int tileX, int tileY);
	void isOnStrove(bool _isOnStove);
	void update(float time);
	void draw(RenderWindow& rw) override;
	bool add(TiledObject* obj) override;
};

class Plate : public Utensil
{
	void changeTexture() override;
	void setStandartTexture() override;
public:
	Plate(Texture& texture);
	Plate(Texture& texture, float _x, float _y);
	bool add(TiledObject* obj) override;
	void draw(RenderWindow& rw) override;
	void update();
};

class Pan : public CookingUtensil
{
	void changeTexture() override;
	void setStandartTexture() override;
public:
	Pan(Texture& texture);
	Pan(Texture& texture, float _x, float _y);
};

