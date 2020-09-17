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
	const int gameTime = 300000;
	float timer;

	void generatePlates();
	void generateCookingUtensils();
	void generateOrders(float time);
	void checkDispencer();
	void checkCutting();
	//returns true if order is completed -> need to remove plate from object list
	bool checkOrders(Plate* plate);
	//returns true if object falls into trash can -> need to remove object from object list
	bool checkTrash(TiledObject* obj);
	void updateUtensil(Utensil* utensil, float time);
	void gameover(int score);
public:
	Game();
	~Game();
	void loop();
};

