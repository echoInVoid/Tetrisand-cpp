#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "setting.h"
#include "render.h"
#include "source.h"
#include "sandData.h"
#include "update.h"
#include "placement.h"

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
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left)
                    placement::curShape.leftRotate();
                else if (event.key.code == sf::Keyboard::Right)
                    placement::curShape.rightRotate();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                    placement::placeSand(&window);
            }
        }
    }

    return 0;
}