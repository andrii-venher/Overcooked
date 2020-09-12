#include "Food.h"

Food::Food(const Food& food) : TiledObject(food)
{ 
	type = ObjectTypes::FOOD; 
	cutBar.setFillColor(Color(255, 0, 0));
}

Food::Food(Texture& texture, int tileX, int tileY) : Food(texture, 0, 0, tileX, tileY) {}

Food::Food(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY)
{
	type = ObjectTypes::FOOD;
	cutBar.setFillColor(Color(255, 0, 0));
}

void Food::cut()
{
	if (cutCounter < cutsNeeded)
		cutCounter++;
	if(cutCounter == cutsNeeded)
	{
		cutBar.setSize(Vector2f(0, 0));
		changeTexture();
		return;
	}
		
	cutBar.setSize(Vector2f(TILE_SIZE / cutsNeeded * cutCounter, 5));
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

void Food::draw(RenderWindow& rw)
{
	TiledObject::draw(rw);
	cutBar.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y + TILE_SIZE / 2);
	rw.draw(cutBar);
}

void Tomato::changeTexture()
{
	if (isCooked())
	{
		sprite.setTextureRect(IntRect(3 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
	else if (isCut())
	{
		sprite.setTextureRect(IntRect(2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	}
}

Tomato::Tomato(Texture& texture) : Tomato(texture, 0, 0) {}

Tomato::Tomato(Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 2) { fType = FoodTypes::TOMATO; }


