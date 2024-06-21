#include <SFML/Graphics.hpp>

#include "render.h"
#include "source.h"

namespace render
{
    static void renderBackground(sf::RenderWindow* window)
    {
        static float offset;
        offset += 0.25;
        offset = offset > 25 ? offset - 25 : offset;
        window->draw(source::getBg());
        source::getBg().setPosition({ -offset, -offset});
    }

    static void renderCover(sf::RenderWindow* window)
    {
        window->draw(source::getCover());
    }

    void renderThread(sf::RenderWindow* window)
    {
        window->setActive(true);
        source::loadSource();

        while (window->isOpen())
        {
            renderBackground(window);
            renderCover(window);
            window->display();
        }
    }
};