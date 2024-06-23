#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>

#include "placement.h"
#include "shape.h"
#include "setting.h"
#include "sandData.h"

namespace placement
{
    shape::Shape curShape = shape::shapes[0];
    int curType = 0;

    int getPlacementX(sf::RenderWindow* window)
    {
        const int blockSize = placement::blockSize * render::sandSize;
        const int ghostW = curShape.w * blockSize;

        int ghostX = sf::Mouse().getPosition(*window).x;
        ghostX = (int)round(layout::sand.getRelPos({ (float)ghostX, 0.0 }).x);
        ghostX -= ghostW / 2;
        ghostX = std::max(ghostX, 0);
        ghostX = std::min(ghostX, (int)round(layout::sand.getSize().x) - ghostW + 1);
        ghostX -= ghostX % render::sandSize;

        return ghostX / render::sandSize;
    }

    void placeSand(sf::RenderWindow* window)
    {
        int placeX = getPlacementX(window);
        sf::Lock lock(sand::sandsLock);

        for (int i = placeX; i < placeX + blockSize * curShape.w; i++)
            for (int j = 0; j < blockSize * curShape.h; j++)
                if (curShape.data[(i - placeX) / blockSize][j / blockSize])
                {
                    if (rand() < RAND_MAX / 2)
                        sand::sands[i][j] = sand::constants::LIGHT[curType];
                    else
                        sand::sands[i][j] = sand::constants::DARK[curType];
                }
    }
}