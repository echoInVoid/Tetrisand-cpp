#pragma once

#include <SFML/Graphics.hpp>

namespace source
{
    namespace colorHint
    {
        extern sf::Sprite prev, cur, next;
        extern sf::Texture prevT, curT, nextT;
    }

    extern sf::Sprite bg, cover, logo;
    extern sf::Font renderFont;

    void refreshHints();

    void loadSource();
};