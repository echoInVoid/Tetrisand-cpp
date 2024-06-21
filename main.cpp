#include <SFML/Graphics.hpp>

#include "setting.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(render::windowW, render::windowH),
        "Tetrisand",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(render::fps);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}