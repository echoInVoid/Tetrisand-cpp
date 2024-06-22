#include <SFML/Graphics.hpp>

#include "render.h"
#include "source.h"
#include "setting.h"
#include "layout.h"
#include "sandData.h"

namespace render
{
    static void renderSand(sf::RenderWindow* window)
    {
        for (int i = 0; i < sand::sandListW; i++)
            for (int j = 0; j < sand::sandListH; j++)
            {
                sf::RectangleShape shape = sand::sands[i][j]->renderShape;
                const sf::Vector2f pos = layout::sand.getPos({ (float)i * render::sandSize , (float)j * render::sandSize });
                shape.setPosition(pos);
                window->draw(shape);
            }
    }

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
            renderSand(window);
            window->display();
        }
    }
};