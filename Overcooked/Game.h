#pragma once
#include "Food.h"
#include "Utensils.h"
#include "Player.h"
#include "Map.h"
#include "Order.h"
#include "Utility.h"

class Game
{
	Player* player;
	Map* map;
	std::list<TiledObject*> objects;
	OrderQueue* queue;
	Texture tileset;

	void generatePlates();
	void generateCookingUtensils();
public:
	Game();
	void loop();
};

