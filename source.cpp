#include <SFML/Graphics.hpp>

#include "setting.h"
#include "source.h"

namespace source
{
    sf::Sprite bg, cover, logo;
    sf::Texture bgTexture, coverTexture, logoTexture;

    void loadSource()
    {
        bgTexture.loadFromFile("./src/bg.png");
        coverTexture.loadFromFile("./src/cover.png");
        logoTexture.loadFromFile("./src/logo.png");
        bg.setTexture(bgTexture);
        cover.setTexture(coverTexture);
        logo.setTexture(logoTexture);
    }
}