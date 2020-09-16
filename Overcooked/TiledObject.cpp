#include "TiledObject.h"

TiledObject::TiledObject(const TiledObject& obj)
{
	this->sprite = obj.sprite;
	this->tileRect = obj.tileRect;
	this->x = obj.x;
	this->y = obj.y;
}

TiledObject::TiledObject(sf::Texture& texture, int tileX, int tileY)
{
	sprite.setTexture(texture);

	tileRect = { tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE };

	sprite.setTextureRect(tileRect);

	sprite.setOrigin(tileRect.width / 2, tileRect.height / 2);

	x = 0;
	y = 0;
}

TiledObject::TiledObject(sf::Texture& texture, float _x, float _y, int tileX, int tileY)
{
	sprite.setTexture(texture);

	tileRect = { tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE };

	sprite.setTextureRect(tileRect);

	sprite.setOrigin(tileRect.width / 2, tileRect.height / 2);

	x = _x;
	y = _y;
	sprite.setPosition(x, y);
}

sf::Sprite TiledObject::getSprite()
{
	return sprite;
}

void TiledObject::setPosition(float _x, float _y)
{
	sprite.setPosition(_x, _y);
}

void TiledObject::setScale(float _factorX, float _factorY)
{
	sprite.setScale(sf::Vector2f(_factorX, _factorY));
}

sf::IntRect TiledObject::getTileRect()
{
	return tileRect;
}

Rotations TiledObject::getRotation()
{
	switch ((int)sprite.getRotation())
	{
	case 90:
		return Rotations::LEFT;
	case 180:
		return Rotations::UP;
	case 270:
		return Rotations::RIGHT;
	case 0:
		return Rotations::DOWN;
	default:
		break;
	}
}

void TiledObject::draw(sf::RenderWindow& rw)
{
	rw.draw(sprite);
}

ObjectTypes TiledObject::getType()
{
	return type;
}
