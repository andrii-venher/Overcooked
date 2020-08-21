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

    objects.push_back(new Food(t, 80, 80, IntRect(32, 32, 32, 32)));

    Player player(t, 16, 16, IntRect(0, 0, 32, 32), objects);

    Map map(t);

    /*Sprite s;
    s.setTexture(t);
    s.setTextureRect(IntRect(0, 0, 32, 32));*/

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
        }

        player.update(time);

        window.clear();
       // window.draw(s);
        map.repaint(window);
        for (TiledObject* obj : objects)
        {
            window.draw(obj->getSprite());
        }
        window.draw(player.getSprite());
        window.draw(player.getInHandsSprite());
        window.display();
    }

    return 0;
}