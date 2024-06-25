#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "setting.h"
#include "render.h"
#include "source.h"
#include "sandData.h"
#include "update.h"
#include "placement.h"
#include "stat.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(render::windowW, render::windowH),
        "Tetrisand",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setActive(false);

    statistics::loadHighScore();
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
                if (!status::gameFailed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        placement::curShape.leftRotate();
                    else if (event.key.code == sf::Keyboard::Right)
                        placement::curShape.rightRotate();
                }
                else
                {
                    sand::reset();
                    statistics::saveHighScore();
                    statistics::score = 0;
                    source::refreshHints();
                    status::gameFailed = false;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                    placement::placeSand(&window);
            }
        }
    }

    statistics::saveHighScore();

    return 0;
}