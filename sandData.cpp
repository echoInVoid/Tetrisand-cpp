#include <SFML/System.hpp>

#include "sandData.h"
#include "setting.h"
#include "sand.h"

namespace sand
{
    const Sand*** sands;
    sf::Mutex sandsLock;

    void initSandData()
    {
        sands = new const Sand**[sandListW];
        for (int i = 0; i < sandListW; i++)
            sands[i] = new const Sand*[sandListH];
        reset();
    }

    void reset()
    {
        for (int i = 0; i < sandListW; i++)
            for (int j = 0; j < sandListH; j++)
                sands[i][j] = &constants::VOID;
    }

    bool validPos(int x, int y)
    {
        return x >= 0 && x < sandListW && y >= 0 && y < sandListH;
    }
}