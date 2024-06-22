#include <SFML/Graphics.hpp>
#include "sand.h"

namespace sand
{
    Sand::Sand(int type, sf::Color color)
    {
        this->type = type;
        this->color = color;
    }

    bool Sand::operator==(Sand s)
    {
        return this->type == s.type;
    }

    bool Sand::operator!=(Sand s)
    {
        return !(*this == s);
    }

    const Sand VOID(-1, sf::Color(0, 0, 0));
    const Sand RED1(0, sf::Color(0xB0482F));
    const Sand RED2(0, sf::Color(0x8D3A26));
    const Sand YELLOW1(1, sf::Color(0xDA9D2F));
    const Sand YELLOW2(1, sf::Color(0xB98628));
    const Sand GREEN1(2, sf::Color(0x5D8D28));
    const Sand GREEN2(2, sf::Color(0x466B1F));
    const Sand BLUE1(3, sf::Color(0x305995));
    const Sand BLUE2(4, sf::Color(0x28497A));
    const Sand REMOVING(4, sf::Color(0xFFFFFF));

    sf::Lock sandsLock(sf::Mutex());

    bool updatableSand(Sand& s)
    {
        return s != VOID && s != REMOVING;
    }
}