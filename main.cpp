#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Roubamonte");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/consola.ttf")) 
    {
        std::cerr << "Error loading font\n";
        return -1; 
    }
    sf::Text text;
    
    text.setFont(font);
    text.setString("Roubamonte");
    text.setCharacterSize(64);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }
    
    return 0;
}
