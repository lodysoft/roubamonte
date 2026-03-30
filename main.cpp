// main.cpp — Roubamonte game entry point.
// Instantiates scene and runs the SFML game loop.

#include <SFML/Graphics.hpp>

#include "scene.h"

static const int N_PLAYERS = 2;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Roubamonte");
    window.setFramerateLimit(60);
 
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/consola.ttf"))
        return -1;

    scene scnGame;
    scnGame.init(font, N_PLAYERS, window.getSize());

    sf::Clock clkFrame;

    while (window.isOpen())
    {
        const float fDelta = clkFrame.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

            scnGame.handle_event(event);
        }

        scnGame.update(fDelta);

        window.clear(sf::Color(34, 100, 34));
        scnGame.draw(window);
        window.display();
    }

    return 0;
}

