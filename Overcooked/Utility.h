#pragma once
#include <SFML/Graphics.hpp>
#include "TiledObject.h"
#include "Food.h"

sf::Vector2i mapPosition(TiledObject* obj);
float convertToMapPosition(int value);
bool checkLists(std::list<Food*> list1, std::list<Food*> list2);