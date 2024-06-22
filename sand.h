#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace sand
{
    class Sand
    {
    public:

        int type;
        sf::RectangleShape renderShape;

        Sand() = default;
        Sand(int t, sf::Color c);
    };

    namespace constants
    {
        extern const Sand VOID, RED1, RED2, YELLOW1, YELLOW2, GREEN1, GREEN2, BLUE1, BLUE2, REMOVING;
        extern const Sand* const LIGHT[4];
        extern const Sand* const DARK[4];
    }

    bool operator==(const Sand& s1, const Sand& s2);
    bool operator!=(const Sand& s1, const Sand& s2);
    bool updatableSand(const Sand& sand);
}