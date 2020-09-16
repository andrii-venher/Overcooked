#include "Utility.h"

sf::Vector2i convertToMapPosition(sf::Vector2f position)
{
    return sf::Vector2i((int)position.x / TILE_SIZE, (int)position.y / TILE_SIZE);
}

sf::Vector2f convertToFloatPosition(sf::Vector2i position)
{
	return sf::Vector2f(position.x * TILE_SIZE + TILE_SIZE / 2, position.y * TILE_SIZE + TILE_SIZE / 2);
}

bool checkListsForEqualFilling(std::list<Food*> list1, std::list<Food*> list2)
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
