#include "Utensils.h"

bool Utensil::isFoodEqualInFilling()
{
	for (auto it = filling.begin(); std::next(it) != filling.end(); it++)
	{
		if ((*it)->getFoodType() != (*(std::next(it)))->getFoodType())
			return false;
	}
	return true;
	
}

Utensil::Utensil(const Utensil& utensils) : TiledObject(utensils)
{
	type = ObjectTypes::UTENSILS;
}

Utensil::Utensil(Texture& texture, int tileX, int tileY) : Utensil(texture, 0, 0, tileX, tileY) {}

Utensil::Utensil(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY)
{
	type = ObjectTypes::UTENSILS;
}

CookingUtensils::CookingUtensils(const CookingUtensils& cookingUtensils) : Utensil(cookingUtensils)
{
	readyBar.setFillColor(Color(255, 0, 0));
}

CookingUtensils::CookingUtensils(Texture& texture, int tileX, int tileY) : CookingUtensils(texture, 0, 0, tileX, tileY) {}

CookingUtensils::CookingUtensils(Texture& texture, float _x, float _y, int tileX, int tileY) : Utensil(texture, _x, _y, tileX, tileY) 
{
	readyBar.setFillColor(Color(255, 0, 0));
}

bool Utensil::add(TiledObject* obj)
{
	if (obj->getType() == ObjectTypes::FOOD && getCapacity() < maxCapacity)
	{
		Food* foodObj = (Food*)obj;
		if (foodObj->isCut())
		{
			filling.push_back(foodObj);
			//std::cout << "Food added, count: " << filling.size() << "\n";
			return true;
		}
	}
	return false;
}

int Utensil::getCapacity()
{
	return filling.size();
}

UtensilType Utensil::getUtensilType()
{
	return utensilType;
}

void CookingUtensils::isOnStrove(bool _isOnStove)
{
	isOnStove = _isOnStove;
}

void CookingUtensils::update(float time)
{
	if (readyTimer > readyTime * getCapacity())
	{
		switchTexture();
		readyBar.setFillColor(Color(0, 255, 0));
		return;
	}
	else
	{
		setStandartTexture();
		readyBar.setFillColor(Color(255, 0, 0));
	}
	if (isOnStove && getCapacity())
	{
		readyTimer += time;
		readyBar.setSize(Vector2f(TILE_SIZE / ((double)readyTime * getCapacity()) * readyTimer, 5));
	}
}

void CookingUtensils::draw(RenderWindow& rw)
{
	TiledObject::draw(rw);
	int shift = 0;
	for (auto it = filling.begin(); it != filling.end(); it++)
	{
		shift += TILE_SIZE / maxCapacity / 2;
		(*it)->setScale((double)1 / maxCapacity, (double)1 / maxCapacity);
		(*it)->setPosition(sprite.getPosition().x - TILE_SIZE / 2 + shift, sprite.getPosition().y - TILE_SIZE / 2 + TILE_SIZE / maxCapacity / 2);
		shift += TILE_SIZE / maxCapacity / 2;
		(*it)->draw(rw);
	}
	readyBar.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y + TILE_SIZE / 2);
	rw.draw(readyBar);
}

void Pan::switchTexture()
{
	if (!isFoodEqualInFilling())
	{
		sprite.setTextureRect(IntRect(3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		return;
	}
	switch (filling.front()->getFoodType())
	{
	case FoodTypes::TOMATO:
		sprite.setTextureRect(IntRect(5 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	default:
		break;
	}
}

void Pan::setStandartTexture()
{
	sprite.setTextureRect(IntRect(2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Pan::Pan(Texture& texture) : CookingUtensils(texture, 2, 1) {}

Pan::Pan(Texture& texture, float _x, float _y) : CookingUtensils(texture, _x, _y, 2, 1) {}

TiledObject* Pan::clone()
{
	return new Pan(*this);
}

void Plate::switchTexture()
{
	if (!isFoodEqualInFilling())
	{
		sprite.setTextureRect(IntRect(1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		return;
	}
	switch (filling.front()->getFoodType())
	{
	case FoodTypes::TOMATO:
		sprite.setTextureRect(IntRect(3 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	default:
		break;
	}
}

void Plate::setStandartTexture()
{
	sprite.setTextureRect(IntRect(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Plate::Plate(const Plate& plate) : Utensil(plate)
{
	utensilType = UtensilType::DISHES;
}

Plate::Plate(Texture& texture) : Plate(texture, 0, 1)
{
}

Plate::Plate(Texture& texture, float _x, float _y) : Utensil(texture, _x, _y, 0, 1)
{
	utensilType = UtensilType::DISHES;
}
