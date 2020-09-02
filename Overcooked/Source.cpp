#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Food.h"
#include <list>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 320), "Overcooked!");

    Texture t;
    t.loadFromFile("Images/tiles.png");

    std::list<TiledObject*> objects;

   // objects.push_back(new Tomato(t, 80, 80));

    Player player(t, 80, 80, objects);

    Map map(t, objects);

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
                if (event.key.code == sf::Keyboard::Space)
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
            }
        }

        player.update(time, map.getMap());

        window.clear();
        map.draw(window);
        for (TiledObject* obj : objects)
        {
            obj->draw(window);
        }
        player.draw(window);
        if (player.isSomethingInHands())
        {
            window.draw(player.getInHandsSprite());
        }
        window.display();
    }

    return 0;
}