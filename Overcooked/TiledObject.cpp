#include "TiledObject.h"

TiledObject::TiledObject(Texture& texture, float _x, float _y, IntRect _tileRect)
{
	sprite.setTexture(texture);

	tileRect = _tileRect;

	sprite.setTextureRect(tileRect);

	sprite.setOrigin(tileRect.width / 2, tileRect.height / 2);

	x = _x;
	y = _y;
}

Sprite TiledObject::getSprite()
{
	return sprite;
}

void TiledObject::setPosition(float _x, float _y)
{
	sprite.setPosition(_x, _y);
}

IntRect TiledObject::getTileRect()
{
	return tileRect;
}
