#include "Utility.h"

sf::Vector2i mapPosition(TiledObject* obj)
{
    return sf::Vector2i((int)obj->getSprite().getPosition().x / TILE_SIZE, (int)obj->getSprite().getPosition().y / TILE_SIZE);
}

float convertToMapPosition(int value)
{
	return value * TILE_SIZE + TILE_SIZE / 2;
}

bool checkLists(std::list<Food*> list1, std::list<Food*> list2)
{
	if (list1.size() != list2.size())
		return false;
	for (auto it1 = std::begin(list1); it1 != std::end(list1); it1++)
	{
		for (auto it2 = std::begin(list2); it2 != std::end(list2); it2++)
		{
			if ((*it1)->getFoodType() == (*it2)->getFoodType() &&
				(*it1)->isCooked() == (*it2)->isCooked())
			{
				list2.erase(it2);
				break;
			}
		}
	}
	if (list2.size() == 0)
		return true;
	else
		return false;
}
