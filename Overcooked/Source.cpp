#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Overcooked!");

    Texture t;
    t.loadFromFile("Images/tiles.png");

    Player player(t, IntRect(0, 0, 32, 32), 16, 16);

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
        window.draw(player.getSprite());
        window.draw(player.getInHands());
        window.display();
    }

    return 0;
}