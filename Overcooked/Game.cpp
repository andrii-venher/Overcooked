#include "Game.h"

Game::Game()
{
	tileset.loadFromFile("Images/tiles.png");
	backgroundTexture.loadFromFile("Images/background.png");
	background.setTexture(backgroundTexture);
	map = new Map(tileset, objects);
	player = new Player(tileset, map->getWidth() * TILE_SIZE / 2 + TILE_SIZE / 2, map->getHeight() * TILE_SIZE / 2 + TILE_SIZE / 2, objects);
	queue = new OrderQueue();
	background.setPosition(map->getWidth() * TILE_SIZE, 0);
	queue->setPosition(map->getWidth() * TILE_SIZE, TILE_SIZE);
	stats = new GameStats(tileset, map->getWidth() * TILE_SIZE, 0);
}

void Game::generatePlates()
{
	int orders = queue->getOrders().size();
	int plates = 0;
	for (const auto& obj : objects)
	{
		if (obj->getType() == ObjectTypes::UTENSILS)
		{
			Utensil* utensil = (Utensil*)obj;
			if (utensil->getUtensilType() == UtensilType::PLATE)
			{
				plates++;
			}
		}
	}
	for (int i = 0; i < orders - plates; i++)
	{
		objects.push_back(new Plate(tileset, convertToMapPosition(0), convertToMapPosition(1)));
	}
}

void Game::generateCookingUtensils()
{
	for (int i = 0; i < map->getHeight(); i++)
	{
		for (int j = 0; j < map->getWidth(); j++)
		{
			if(map->at(j, i) == MapObjects::STOVE)
				objects.push_back(new Pan(tileset, convertToMapPosition(j), convertToMapPosition(i)));
		}
	}
}

void Game::generateOrders(float time)
{
	static float timer = 0.0;
	if (queue->getOrders().size() == 0)
	{
		RandomOrderFactory randomOrderFactory(tileset);
		queue->add(randomOrderFactory.create());
	}
	if (timer < queue->getOrders().front()->getOrderTime() * 0.4)
	{
		timer += time;
	}
	else
	{
		RandomOrderFactory randomOrderFactory(tileset);
		queue->add(randomOrderFactory.create());
		timer = 0;
	}
}

void Game::loop()
{
	RenderWindow window(VideoMode(TILE_SIZE * map->getWidth() + TILE_SIZE * 3 + 6, TILE_SIZE * map->getHeight()), "Overcooked!", 
		sf::Style::Close);
	Clock clock;

	generateCookingUtensils();

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		time /= 500;
		clock.restart();

		generatePlates();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (player->isSomethingInHands())
					{
						player->put();
						continue;
					}
					else
					{
						player->take();
					}

					if (!player->isSomethingInHands())
					{
						if (map->interact(player->getNextPosition().first, player->getNextPosition().second) == Actions::TAKE)
						{
							player->take();
						}
					}
				}
				if (event.key.code == sf::Keyboard::Tab)
				{
					map->fabricate(player->getNextPosition().first, player->getNextPosition().second);
				}
			}
		}

		player->update(time, map->getMap());

		window.clear();
		window.draw(background);
		map->draw(window);
		std::vector<TiledObject*> removedElements;
		for (TiledObject* obj : objects)
		{
			obj->draw(window);
			Vector2i pos = mapPosition(obj);
			switch (obj->getType())
			{
			case ObjectTypes::UTENSILS:
			{
				Utensil* utensil = (Utensil*)obj;
				if (map->at(pos.x, pos.y) == MapObjects::TRASH)
				{
					utensil->clear();
				}
				if (utensil->getUtensilType() == UtensilType::COOKING)
				{
					CookingUtensil* cookingUtensil = (CookingUtensil*)utensil;
					cookingUtensil->update(time);
					if (map->at(pos.x, pos.y) == MapObjects::STOVE)
					{
						cookingUtensil->onStove();
					}
					else
					{
						cookingUtensil->offStove();
					}
				}
				else if (utensil->getUtensilType() == UtensilType::PLATE)
				{
					Plate* plate = (Plate*)utensil;
					plate->update();
					if (map->at(pos.x, pos.y) == MapObjects::CHECKOUT)
					{
						plate->onCheckout();
					}
					else
					{
						plate->offCheckout();
					}
					if (plate->isOnCheckout())
					{
						auto orderList = queue->getOrders();

						for (const auto& order : orderList)
						{
							if (checkLists(order->getList(), plate->getList()))
							{
								order->complete();
								delete plate;
								removedElements.push_back(obj);
								break;
							}
						}
					}
				}
				break;
			}
			case ObjectTypes::FOOD:
			{
				Food* food = (Food*)obj;
				if (map->at(pos.x, pos.y) == MapObjects::TRASH)
				{
					delete food;
					removedElements.push_back(obj);
					break;
				}
				break;
			}
			default:
				break;
			}
		}
		for (auto el : removedElements)
		{
			objects.remove(el);
		}
		player->draw(window);

		generateOrders(time);
		queue->update(time);
		queue->draw(window);

		stats->update(time, queue->getTips());
		stats->draw(window);

		window.display();
	}
}
