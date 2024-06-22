#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "setting.h"
#include "render.h"
#include "source.h"
#include "sandData.h"
#include "update.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(render::windowW, render::windowH),
        "Tetrisand",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setActive(false);

    sand::initSandData();

    sf::Thread renderThread(render::renderThread, &window);
    renderThread.launch();

    sf::Thread updateThread(update::updateThread, &window);
    updateThread.launch();
    
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