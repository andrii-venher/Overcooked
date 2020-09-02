#include "Food.h"

Food::Food(Texture& texture, float _x, float _y, int tileX, int tileY) : TiledObject(texture, _x, _y, tileX, tileY)
{
}

Tomato::Tomato(Texture& texture, float _x, float _y) : Food(texture, _x, _y, 1, 1) {}
