#pragma once
#include "Food.h"
#include "Utensils.h"
#include "Player.h"
#include "Map.h"
#include "Order.h"
#include "Utility.h"
#include "GameStats.h"

class Game
{
	Player* player;
	Map* map;
	std::list<TiledObject*> objects;
	OrderQueue* queue;
	Texture tileset;
	Sprite background;
	Texture backgroundTexture;
	GameStats* stats;

	void generatePlates();
	void generateCookingUtensils();
	void generateOrders(float time);
public:
	Game();
	void loop();
};

