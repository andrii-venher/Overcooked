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

    objects.push_back(new Food(t, 80, 80, 1, 1));
    //objects.push_back(new Food(t, 160, 160, 1, 0));

    Player player(t, 16, 16, 0, 0, objects);

    Map map(t);

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
                        player.putFromHands();
                    }
                    else
                    {
                        player.takeIntoHands();
                    }
                }
            }
        }

        player.update(time);

        window.clear();
        map.repaint(window);
        for (TiledObject* obj : objects)
        {
            window.draw(obj->getSprite());
        }
        window.draw(player.getSprite());
        if (player.isSomethingInHands())
        {
            window.draw(player.getInHandsSprite());
        }
        window.display();
    }

    return 0;
}