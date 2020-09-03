#include "Food.h"

Food::Food(const Food& food) : TiledObject(food) { type = ObjectTypes::FOOD; }

Food::Food(Texture& texture, int tileX, int tileY) : TiledObject(texture, tileX, tileY) { type = ObjectTypes::FOOD; }

Food::Food(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY) { type = ObjectTypes::FOOD; }

void Food::cut()
{
	cutCounter++;
	if (cutCounter == 4)
		changeTexture();
}

bool Food::isCut()
{
	return (cutCounter >= 4) ? true : false;
}

void Tomato::changeTexture()
{
	IntRect tileRect = getTileRect();
	tileRect.left = 2 * TILE_SIZE;
	sprite.setTextureRect(tileRect);
}

Tomato::Tomato(Texture& texture) : Food(texture, 1, 1) {}

Tomato::Tomato(Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 1) {}

TiledObject* Tomato::clone()
{
	return new Tomato(*this);
}

FoodFactory::FoodFactory(Texture& t)
{
	prototypes[FoodTypes::TOMATO] = new Tomato(t);
}

FoodFactory::~FoodFactory()
{
	delete prototypes[FoodTypes::TOMATO];	
}

TiledObject* FoodFactory::create(FoodTypes type, float _x = 0, float _y = 0)
{
	TiledObject* obj = prototypes[type]->clone();
	obj->setPosition(_x, _y);
	return obj;
}
