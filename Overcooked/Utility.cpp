#include "Utility.h"

sf::Vector2f convertPosition(TiledObject* obj)
{
    return sf::Vector2f((int)obj->getSprite().getPosition().x / TILE_SIZE, (int)obj->getSprite().getPosition().y / TILE_SIZE);
}
