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
	Utensil(sf::Texture& texture, int tileX, int tileY);
	Utensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	~Utensil();
	int getCapacity();
	virtual bool add(TiledObject* obj) = 0;
	void moveToUtensil(Utensil* utensil);
	void clear();
	UtensilType getUtensilType();
};

class CookingUtensil : public Utensil
{
protected:
	const int readyTime = 1000;
	int readyTimer = 0;
	bool stove = false;
	sf::RectangleShape readyBar;
public:
	CookingUtensil(sf::Texture& texture, int tileX, int tileY);
	CookingUtensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	bool add(TiledObject* obj) override;
	void update(float time);
	void onStove();
	void offStove();
	void draw(sf::RenderWindow& rw) override;
};

class Plate : public Utensil
{
	bool checkout = false;
	void changeTexture() override;
	void setStandartTexture() override;
public:
	Plate(sf::Texture& texture);
	Plate(sf::Texture& texture, float _x, float _y);
	bool add(TiledObject* obj) override;
	void update();
	void onCheckout();
	void offCheckout();
	bool isOnCheckout();
	std::list<Food*> getFilling();
	void draw(sf::RenderWindow& rw) override;
};

class Pan : public CookingUtensil
{
	void changeTexture() override;
	void setStandartTexture() override;
public:
	Pan(sf::Texture& texture);
	Pan(sf::Texture& texture, float _x, float _y);
};

