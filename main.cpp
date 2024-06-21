#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "setting.h"
#include "render.h"[
#include "source.h"]

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(render::windowW, render::windowH),
        "Tetrisand",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(render::fps);
    window.setActive(false);

    sf::Thread renderThread(render::renderThread, &window);
    renderThread.launch();
    
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