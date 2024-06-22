#include <SFML/Graphics.hpp>
#include <algorithm>

#include "render.h"
#include "source.h"
#include "setting.h"
#include "layout.h"
#include "sandData.h"
#include "status.h"

namespace render
{
    static void renderShapeHint(sf::RenderWindow* window)
    {
        shape::Shape& curShape = placement::curShape;
        const int w = curShape.w * render::hintBlockSize;
        const int h = curShape.h * render::hintBlockSize;
        const float x = layout::shape.getSize().x / 2 - w / 2.0;
        const float y = layout::shape.getSize().y / 2 - h / 2.0;

        auto s = sf::RectangleShape({ render::hintBlockSize, render::hintBlockSize });
        s.setFillColor(sf::Color(0xFFFFFFFF));
        for (int i = 0; i < curShape.w; i++)
            for (int j = 0; j < curShape.h; j++)
                if (curShape.data[i][j])
                {
                    s.setPosition(
                        layout::shape.getAbsPos({
                            x + i * render::hintBlockSize,
                            y + j * render::hintBlockSize
                        })
                    );
                    window->draw(s);
                }
    }

    static void renderGhost(sf::RenderWindow* window)
    {
        shape::Shape& curShape = placement::curShape;
        const int blockSize = placement::blockSize * render::sandSize;
        const int ghostW = curShape.w * blockSize;

        int ghostX = sf::Mouse().getPosition(*window).x;
        ghostX = (int)round(layout::sand.getRelPos({ (float)ghostX, 0.0 }).x);
        ghostX -= ghostW / 2;
        ghostX = std::max(ghostX, 0);
        ghostX = std::min(ghostX, (int)round(layout::sand.getSize().x) - ghostW + 1);
        ghostX -= ghostX % render::sandSize;

        sf::Color ghostC = sand::constants::LIGHT[placement::curType]->renderShape.getFillColor();
        ghostC.a = 100;

        auto s = sf::RectangleShape({ blockSize,  blockSize });
        s.setFillColor(ghostC);

        for (int i=0; i<curShape.w; i++)
            for (int j=0; j<curShape.h; j++)
                if (curShape.data[i][j])
                {
                    s.setPosition(layout::sand.getAbsPos({ (float)ghostX + blockSize * i, (float)blockSize * j }));
                    window->draw(s);
                }
    }

    static void renderSand(sf::RenderWindow* window)
    {
        for (int i = 0; i < sand::sandListW; i++)
            for (int j = 0; j < sand::sandListH; j++)
            {
                sf::RectangleShape shape = sand::sands[i][j]->renderShape;
                const sf::Vector2f pos = layout::sand.getAbsPos({ (float)i * render::sandSize , (float)j * render::sandSize });
                shape.setPosition(pos);
                window->draw(shape);
            }
    }

    static void renderLogo(sf::RenderWindow* window)
    {
        const sf::Vector2f pos = layout::info.getAbsPos({ 0,0 });
        source::logo.setPosition(pos);
        window->draw(source::logo);
    }

    static void renderBackground(sf::RenderWindow* window)
    {
        static float offset;
        offset += 0.25;
        offset = offset > 25 ? offset - 25 : offset;
        window->draw(source::bg);
        source::bg.setPosition({ -offset, -offset });
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
            renderGhost(window);
            renderShapeHint(window);
            window->display();
        }
    }
};