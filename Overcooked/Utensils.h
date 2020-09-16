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
	Utensil(sf::Texture& texture, int tileX, int tileY);
	Utensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	~Utensil();
	virtual bool add(TiledObject* obj) = 0;
	int getCapacity();
	void moveToUtensil(Utensil* utensil);
	void clear();
	UtensilType getUtensilType();
};

class CookingUtensil : public Utensil
{
protected:
	int readyTimer = 0;
	bool stove = false;
	sf::RectangleShape readyBar;
	const int readyTime = 1000;
public:
	CookingUtensil(const CookingUtensil& cookingUtensils);
	CookingUtensil(sf::Texture& texture, int tileX, int tileY);
	CookingUtensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY);
	void onStove();
	void offStove();
	void update(float time);
	void draw(sf::RenderWindow& rw) override;
	bool add(TiledObject* obj) override;
};

class Plate : public Utensil
{
	void changeTexture() override;
	void setStandartTexture() override;
	bool checkout = false;
public:
	Plate(sf::Texture& texture);
	Plate(sf::Texture& texture, float _x, float _y);
	bool add(TiledObject* obj) override;
	void draw(sf::RenderWindow& rw) override;
	void update();
	void onCheckout();
	void offCheckout();
	bool isOnCheckout();
	std::list<Food*> getList();
};

class Pan : public CookingUtensil
{
	void changeTexture() override;
	void setStandartTexture() override;
public:
	Pan(sf::Texture& texture);
	Pan(sf::Texture& texture, float _x, float _y);
};

