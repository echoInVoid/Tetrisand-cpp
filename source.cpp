#include <SFML/Graphics.hpp>
#include <boost/format.hpp>

#include "setting.h"
#include "source.h"
#include "placement.h"

namespace source
{
    namespace colorHint
    {
        sf::Sprite prev, cur, next;
        sf::Texture prevT, curT, nextT;
    }

    sf::Sprite bg, cover, logo;
    sf::Texture bgTexture, coverTexture, logoTexture;
    sf::Font renderFont;

    void refreshHints()
    {
        using namespace colorHint;
        using boost::format;

        prevT = curT;
        curT.loadFromFile((format(".\\src\\sand\\%d.png") % placement::curType).str());
        nextT.loadFromFile((format(".\\src\\sand\\%d.png") % placement::nextType).str());

        prev.setTexture(prevT, true);
        cur.setTexture(curT, true);
        next.setTexture(nextT, true);
    }

    void loadSource()
    {
        renderFont.loadFromFile(".\\src\\HighPixel.ttf");

        bgTexture.loadFromFile(".\\src\\bg.png");
        coverTexture.loadFromFile(".\\src\\cover.png");
        logoTexture.loadFromFile(".\\src\\logo.png");
        bg.setTexture(bgTexture);
        cover.setTexture(coverTexture);
        logo.setTexture(logoTexture);

        using boost::format;
        using colorHint::curT;
        curT.loadFromFile((format(".\\src\\sand\\%d.png") % placement::curType).str());
        refreshHints();
    }
}