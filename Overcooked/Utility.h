#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"
#include "Food.h"
#include <list>

sf::Vector2i convertToMapPosition(sf::Vector2f position);
sf::Vector2f convertToFloatPosition(sf::Vector2i position);
bool checkListsForEqualFilling(std::list<Food*> list1, std::list<Food*> list2);