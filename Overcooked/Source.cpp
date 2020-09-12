#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Food.h"
#include "Utensils.h"
#include "Order.h"
#include <list>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 320), "Overcooked!");

    Texture t;
    t.loadFromFile("Images/tiles.png");

   /* std::list<TiledObject*> objects;

    CookingUtensil* pan = new Pan(t, 48, 16);

    Plate* plate = new Plate(t, 80, 80);

    objects.push_back(pan);
    objects.push_back(plate);

    Player player(t, 80, 80, objects);

    Map map(t, objects);*/

    Order* order1 = new TomatoSoupOrder(t);

    Order* order2 = new TomatoSoupOrder(t);

    OrderQueue queue;
    queue.add(order1);
    queue.add(order2);
    queue.setPosition(50, 70);
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        time /= 500;
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                /*if (event.key.code == sf::Keyboard::Space)
                {
                    if (player.isSomethingInHands())
                    {
                        player.put();
                        continue;
                    }
                    else
                    {
                        player.take();
                    }

                    if (!player.isSomethingInHands())
                    {
                        if (map.interact(player.getNextPosition().first, player.getNextPosition().second) == Actions::TAKE)
                        {
                            player.take();
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Tab)
                {
                    map.fabricate(player.getNextPosition().first, player.getNextPosition().second);
                }*/
            }
        }

        //player.update(time, map.getMap());
        //map.update();

        window.clear();
        //map.draw(window);
       /* for (TiledObject* obj : objects)
        {
            obj->draw(window);
            switch (obj->getType())
            {
            case ObjectTypes::UTENSILS:
            {
                Utensil* utenObj = (Utensil*)obj;
                if (utenObj->getUtensilType() == UtensilType::COOKING)
                {
                    CookingUtensil* cookingUtensil = (CookingUtensil*)utenObj;
                    cookingUtensil->update(time);
                }
                else if (utenObj->getUtensilType() == UtensilType::PLATE)
                {
                    Plate* plateUtensil = (Plate*)utenObj;
                    plate->update();
                }
            }
            default:
                break;
            }
        }
        player.draw(window);*/
        queue.update(time);
        queue.draw(window);
        window.display();
    }

    return 0;
}