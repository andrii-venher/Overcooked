#include "Utensils.h"

Utensils::Utensils(const Utensils& food) : TiledObject(food)
{
	type = ObjectTypes::UTENSILS; 
	readyBar.setFillColor(Color(0, 0, 0));
}

Utensils::Utensils(Texture& texture, int tileX, int tileY) : TiledObject(texture, tileX, tileY)
{ 
	type = ObjectTypes::UTENSILS;
	readyBar.setFillColor(Color(0, 0, 0));
}

Utensils::Utensils(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY) 
{
	type = ObjectTypes::UTENSILS;
	readyBar.setFillColor(Color(0, 0, 0));
}

bool Utensils::add(TiledObject* obj)
{
	if (obj->getType() == ObjectTypes::FOOD && filling.size() < 3)
	{
		Food* foodObj = (Food*)obj;
		if (foodObj->isCut())
		{
			filling.push_back(foodObj);
			std::cout << "Food added, count: " << filling.size() << "\n";
			return true;
		}
	}
	return false;
}

int Utensils::getFillingSize()
{
	return filling.size();
}

void Utensils::setStove(bool _isOnStove)
{
	isOnStove = _isOnStove;
}

void Utensils::update(float time)
{
	if (readyTimer > 500)
	{
		IntRect tileRect = getTileRect();
		tileRect.left = 2 * TILE_SIZE;
		tileRect.top = 2 * TILE_SIZE;
		sprite.setTextureRect(tileRect);
		return;
	}
	if (isOnStove && filling.size() > 0)
	{
		readyTimer += time;
		readyBar.setSize(Vector2f(TILE_SIZE / (double)500 * readyTimer, 5));
	}
}

void Utensils::draw(RenderWindow& rw)
{
	TiledObject::draw(rw);
	readyBar.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y + TILE_SIZE / 2);
	rw.draw(readyBar);
}

Pan::Pan(Texture& texture) : Utensils(texture, 0, 2) {}

Pan::Pan(Texture& texture, float _x, float _y) : Utensils(texture, _x, _y, 0, 2) {}

TiledObject* Pan::clone()
{
	return new Pan(*this);
}
