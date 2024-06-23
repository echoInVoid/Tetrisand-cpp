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
    sf::Clock placeClock = sf::Clock();

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

    // ��������ȴ�Ƿ����
    static bool checkCD()
    {
        return placeClock.getElapsedTime().asSeconds() >= placeCD;
    }
    
    // ��齫Ҫ���õ�ɳ���Ƿ����Ѿ����ڵ�ɳ���ص�
    static bool checkOverlapping(int placeX)
    {
        for (int i = placeX; i < placeX + blockSize * curShape.w; i++)
            for (int j = 0; j < blockSize * curShape.h; j++)
                if (curShape.data[(i - placeX) / blockSize][j / blockSize] && sand::updatableSand(*sand::sands[i][j]))
                    return true;
        return false;
    }

    void placeSand(sf::RenderWindow* window)
    {
        if (!checkCD())
            return;

        int placeX = getPlacementX(window);
        sf::Lock lock(sand::sandsLock);

        if (checkOverlapping(placeX))
            return;

        for (int i = placeX; i < placeX + blockSize * curShape.w; i++)
            for (int j = 0; j < blockSize * curShape.h; j++)
                if (curShape.data[(i - placeX) / blockSize][j / blockSize])
                {
                    if (rand() < RAND_MAX / 2)
                        sand::sands[i][j] = sand::constants::LIGHT[curType];
                    else
                        sand::sands[i][j] = sand::constants::DARK[curType];
                }

        placeClock.restart();
    }
}