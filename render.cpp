#include <SFML/Graphics.hpp>

#include "render.h"
#include "source.h"
#include "setting.h"
#include "layout.h"

namespace render
{
    static void renderLogo(sf::RenderWindow* window)
    {
        const sf::Vector2f pos = layout::info.getPos({ 0,0 });
        source::logo.setPosition(pos);
        window->draw(source::logo);
    }

    static void renderBackground(sf::RenderWindow* window)
    {
        static float offset;
        offset += 0.25;
        offset = offset > 25 ? offset - 25 : offset;
        window->draw(source::bg);
        source::bg.setPosition({ -offset, -offset});
    }

    static void renderCover(sf::RenderWindow* window)
    {
        window->draw(source::cover);
    }

    void renderThread(sf::RenderWindow* window)
    {
        window->setFramerateLimit(render::fps);
        window->setActive(true);
        source::loadSource();

        while (window->isOpen())
        {
            renderBackground(window);
            renderCover(window);
            renderLogo(window);
            window->display();
        }
    }
};