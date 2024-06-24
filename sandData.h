#pragma once

#include <SFML/System.hpp>

#include "sand.h"
#include "setting.h"

namespace sand
{
    extern const Sand*** sands; // Sand* sands[sandListW][sandListH];
    extern sf::Mutex sandsLock;

    void initSandData();
    void reset();

    bool validPos(int x, int y);
}