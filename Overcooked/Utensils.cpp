#include "Utensils.h"

bool Utensils::isFoodEqualInFilling()
{
	for (auto it = filling.begin(); std::next(it) != filling.end(); it++)
	{
		if ((*it)->getFoodType() != (*(std::next(it)))->getFoodType())
			return false;
	}
	return true;
	
}

Utensils::Utensils(const Utensils& food) : TiledObject(food)
{
	type = ObjectTypes::UTENSILS; 
	readyBar.setFillColor(Color(255, 0, 0));
}

Utensils::Utensils(Texture& texture, int tileX, int tileY) : Utensils(texture, 0, 0, tileX, tileY) {}

Utensils::Utensils(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY) 
{
	type = ObjectTypes::UTENSILS;
	readyBar.setFillColor(Color(255, 0, 0));
}

bool Utensils::add(TiledObject* obj)
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

int Utensils::getCapacity()
{
	return filling.size();
}

void Utensils::isOnStrove(bool _isOnStove)
{
	isOnStove = _isOnStove;
}

void Utensils::update(float time)
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
	}
	if (isOnStove && getCapacity())
	{
		readyTimer += time;
		readyBar.setSize(Vector2f(TILE_SIZE / ((double)readyTime * getCapacity()) * readyTimer, 5));
	}
}

void Utensils::draw(RenderWindow& rw)
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
		sprite.setTextureRect(IntRect(0 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		return;
	}
	switch (filling.front()->getFoodType())
	{
	case FoodTypes::TOMATO:
		sprite.setTextureRect(IntRect(2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	default:
		break;
	}
}

void Pan::setStandartTexture()
{
	sprite.setTextureRect(IntRect(0 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Pan::Pan(Texture& texture) : Utensils(texture, 0, 2) {}

Pan::Pan(Texture& texture, float _x, float _y) : Utensils(texture, _x, _y, 0, 2) {}

TiledObject* Pan::clone()
{
	return new Pan(*this);
}
