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

    void refreshHints();

    void loadSource();
};