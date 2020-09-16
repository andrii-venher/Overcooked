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
	sf::Texture tileset;
	sf::Sprite background;
	sf::Texture backgroundTexture;
	GameStats* stats;

	void generatePlates();
	void generateCookingUtensils();
	void generateOrders(float time);
	void checkDispencer();
	void checkCutting();
public:
	Game();
	void loop();
};

