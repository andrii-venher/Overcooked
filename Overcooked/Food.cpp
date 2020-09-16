#include "Food.h"

Food::Food(const Food& food) : TiledObject(food)
{ 
	type = ObjectTypes::FOOD; 
	cutBar.setFillColor(sf::Color(255, 0, 0));
}

Food::Food(sf::Texture& texture, int tileX, int tileY) : Food(texture, 0, 0, tileX, tileY) {}

Food::Food(sf::Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY)
{
	type = ObjectTypes::FOOD;
	cutBar.setFillColor(sf::Color(255, 0, 0));
}

void Food::cut()
{
	if (cutCounter < cutsNeeded)
		cutCounter++;
	if(cutCounter == cutsNeeded)
	{
		cutBar.setSize(sf::Vector2f(0, 0));
		changeTexture();
		return;
	}
		
	cutBar.setSize(sf::Vector2f(TILE_SIZE / cutsNeeded * cutCounter, 5));
}

bool Food::isCut()
{
	return (cutCounter >= cutsNeeded) ? true : false;
}

void Food::setCooked()
{
	cooked = true;
	changeTexture();
}

bool Food::isCooked()
{
	return (cooked) ? true : false;
}

FoodTypes Food::getFoodType()
{
	return fType;
}

void Food::draw(sf::RenderWindow& rw)
{
	TiledObject::draw(rw);
	cutBar.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y + TILE_SIZE / 2);
	rw.draw(cutBar);
}

void Tomato::changeTexture()
{
	if (isCooked())
	{
		sprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
	else if (isCut())
	{
		sprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
}

Tomato::Tomato(sf::Texture& texture) : Tomato(texture, 0, 0) {}

Tomato::Tomato(sf::Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 2) { fType = FoodTypes::TOMATO; }

void Mushroom::changeTexture()
{
	if (isCooked())
	{
		sprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
	else if (isCut())
	{
		sprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
}

Mushroom::Mushroom(sf::Texture& texture) : Mushroom(texture, 0, 0) {}

Mushroom::Mushroom(sf::Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 3) { fType = FoodTypes::MUSHROOM; }

void Onion::changeTexture()
{
	if (isCooked())
	{
		sprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
	else if (isCut())
	{
		sprite.setTextureRect(sf::IntRect(2 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
}

Onion::Onion(sf::Texture& texture) : Onion(texture, 0, 0) {}

Onion::Onion(sf::Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 4) { fType = FoodTypes::ONION; }

