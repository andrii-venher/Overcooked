#include "Utensils.h"

bool Utensil::isFoodEqualInFilling()
{
	if (!getCapacity())
	{
		return false;
	}
	for (auto it = filling.begin(); std::next(it) != filling.end(); it++)
	{
		if ((*it)->getFoodType() != (*(std::next(it)))->getFoodType() || 
			(*it)->isCut() != (*(std::next(it)))->isCut() ||
			(*it)->isCooked() != (*(std::next(it)))->isCooked())
			return false;
	}
	return true;
	
}

Utensil::Utensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY)
{
	type = ObjectTypes::UTENSIL;
}

Utensil::~Utensil()
{
	while (filling.size())
	{
		delete filling.front();
		filling.pop_front();
	}
}

CookingUtensil::CookingUtensil(sf::Texture& texture, int tileX, int tileY) : CookingUtensil(texture, 0, 0, tileX, tileY) {}

CookingUtensil::CookingUtensil(sf::Texture& texture, float _x, float _y, int tileX, int tileY) : Utensil(texture, _x, _y, tileX, tileY)
{
	readyBar.setFillColor(sf::Color(255, 0, 0));
}

int Utensil::getCapacity()
{
	return filling.size();
}

void Utensil::moveToUtensil(Utensil* utensil)
{
	if (getCapacity())
	{
		std::vector<std::list<Food*>::iterator> removedElements;
		for (auto it = std::begin(filling); it != std::end(filling); it++)
		{
			if (utensil->add(*it))
				removedElements.push_back(it);
		}
		for (int i = 0; i < removedElements.size(); i++)
		{
			filling.erase(removedElements[i]);
		}
	}
}

void Utensil::clear()
{
	filling.clear();
}

UtensilType Utensil::getUtensilType()
{
	return utensilType;
}

void CookingUtensil::onStove()
{
	stove = true;
}

void CookingUtensil::offStove()
{
	stove = false;
}

void CookingUtensil::update(float time)
{
	if (!getCapacity())
	{
		readyTimer = 0;
		setStandartTexture();
		readyBar.setSize(sf::Vector2f(0, 0));
		return;
	}
	if (readyTimer > readyTime * getCapacity())
	{
		changeTexture();
		readyBar.setFillColor(sf::Color(0, 255, 0));
		for (const auto& food : filling)
		{
			food->setCooked();
		}
		return;
	}
	else
	{
		setStandartTexture();
		readyBar.setFillColor(sf::Color(255, 0, 0));
	}
	if (stove)
	{
		readyTimer += time;
		readyBar.setSize(sf::Vector2f(TILE_SIZE / ((double)readyTime * getCapacity()) * readyTimer, 5));
	}
}

void CookingUtensil::draw(sf::RenderWindow& rw)
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
	readyBar.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y + TILE_SIZE / 2 - 5);
	rw.draw(readyBar);
}

bool CookingUtensil::add(TiledObject* obj)
{
	if (obj->getType() == ObjectTypes::FOOD && getCapacity() < maxCapacity)
	{
		Food* foodObj = (Food*)obj;
		if (foodObj->isCut() && !foodObj->isCooked())
		{
			filling.push_back(foodObj);
			return true;
		}
	}
	return false;
}

void Pan::changeTexture()
{
	if (!isFoodEqualInFilling())
	{
		sprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		return;
	}
	if (getCapacity())
	{
		switch (filling.front()->getFoodType())
		{
		case FoodTypes::TOMATO:
			sprite.setTextureRect(sf::IntRect(7 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			break;
		case FoodTypes::MUSHROOM:
			sprite.setTextureRect(sf::IntRect(7 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			break;
		case FoodTypes::ONION:
			sprite.setTextureRect(sf::IntRect(7 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
			break;
		default:
			break;
		}
	}
	
}

void Pan::setStandartTexture()
{
	sprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Pan::Pan(sf::Texture& texture) : CookingUtensil(texture, 2, 1) {}

Pan::Pan(sf::Texture& texture, float _x, float _y) : CookingUtensil(texture, _x, _y, 2, 1) {}

void Plate::changeTexture()
{
	if (!isFoodEqualInFilling())
	{
		sprite.setTextureRect(sf::IntRect(1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		return;
	}
	switch (filling.front()->getFoodType())
	{
	case FoodTypes::TOMATO:
		
		if (filling.front()->isCooked())
			sprite.setTextureRect(sf::IntRect(6 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else if(filling.front()->isCut())
			sprite.setTextureRect(sf::IntRect(5 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else
			sprite.setTextureRect(sf::IntRect(4 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		break;
	case FoodTypes::MUSHROOM:

		if (filling.front()->isCooked())
			sprite.setTextureRect(sf::IntRect(6 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else if (filling.front()->isCut())
			sprite.setTextureRect(sf::IntRect(5 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else
			sprite.setTextureRect(sf::IntRect(4 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		break;
	case FoodTypes::ONION:

		if (filling.front()->isCooked())
			sprite.setTextureRect(sf::IntRect(6 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else if (filling.front()->isCut())
			sprite.setTextureRect(sf::IntRect(5 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		else
			sprite.setTextureRect(sf::IntRect(4 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
		break;
	default:
		break;
	}
}

void Plate::setStandartTexture()
{
	sprite.setTextureRect(sf::IntRect(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

Plate::Plate(sf::Texture& texture) : Plate(texture, 0, 1) {}

Plate::Plate(sf::Texture& texture, float _x, float _y) : Utensil(texture, _x, _y, 0, 1)
{
	utensilType = UtensilType::PLATE;
}

bool Plate::add(TiledObject* obj)
{
	if (obj->getType() == ObjectTypes::FOOD && getCapacity() < maxCapacity)
	{
		Food* foodObj = (Food*)obj;
		filling.push_back(foodObj);
		return true;
	}
	return false;
}

void Plate::draw(sf::RenderWindow& rw)
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
}

void Plate::update()
{
	if (getCapacity())
	{
		changeTexture();
	}
	else
	{
		setStandartTexture();
	}
}

void Plate::onCheckout()
{
	checkout = true;
}

void Plate::offCheckout()
{
	checkout = false;
}

bool Plate::isOnCheckout()
{
	return checkout;
}

std::list<Food*> Plate::getFilling()
{
	return filling;
}
