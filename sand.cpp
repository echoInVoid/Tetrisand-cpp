#include <SFML/Graphics.hpp>
#include "sand.h"
#include "setting.h"

namespace sand
{
    Sand::Sand(int type, sf::Color color)
    {
        this->type = type;
        this->renderShape = sf::RectangleShape({ render::sandSize , render::sandSize });
        this->renderShape.setFillColor(color);
    }

    bool operator==(const Sand& s1, const Sand& s2)
    {
        return s1.type == s2.type;
    }

    bool operator!=(const Sand& s1, const Sand& s2)
    {
        return !(s1 == s2);
    }

    bool updatableSand(const Sand& s)
    {
        return s != constants::VOID && s != constants::REMOVING;
    }

    namespace constants
    {
        const Sand VOID(-1, sf::Color(0x000000FF));
        const Sand RED1(0, sf::Color(0xB0482FFF));
        const Sand RED2(0, sf::Color(0x8D3A26FF));
        const Sand YELLOW1(1, sf::Color(0xDA9D2FFF));
        const Sand YELLOW2(1, sf::Color(0xB98628FF));
        const Sand GREEN1(2, sf::Color(0x5D8D28FF));
        const Sand GREEN2(2, sf::Color(0x466B1FFF));
        const Sand BLUE1(3, sf::Color(0x305995FF));
        const Sand BLUE2(4, sf::Color(0x28497AFF));
        const Sand REMOVING(4, sf::Color(0xFFFFFFFF));

        const Sand* const LIGHT[4] = { &RED1, &YELLOW1, &GREEN1, &BLUE1 };
        const Sand* const DARK[4] = { &RED2, &YELLOW2, &GREEN2, &BLUE2 };
    }
}