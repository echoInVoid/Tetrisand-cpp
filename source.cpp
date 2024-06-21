#include <SFML/Graphics.hpp>

#include "setting.h"
#include "source.h"

namespace source
{
    sf::Sprite bg, cover;
    sf::Texture bgTexture, coverTexture;

    void loadSource()
    {
        bgTexture.loadFromFile("./src/bg.png");
        coverTexture.loadFromFile("./src/cover.png");
        bg.setTexture(bgTexture);
        cover.setTexture(coverTexture);
    }

    sf::Sprite& getBg()
    {
        return bg;
    }

    sf::Sprite& getCover()
    {
        return cover;
    }
}