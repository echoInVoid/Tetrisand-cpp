#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <ctime>

#include "placement.h"
#include "shape.h"
#include "setting.h"
#include "sandData.h"
#include "source.h"

namespace placement
{
    shape::Shape curShape = shape::shapes[0];
    int curType = 0;
    int nextType = 0; // 下下个放置的颜色
    sf::Clock placeClock = sf::Clock();
    bool placed = false;

    float sinceLastPlacement()
    {
        return placeClock.getElapsedTime().asSeconds();
    }

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

    // 检查放置冷却是否完成
    static bool checkCD()
    {
        return placeClock.getElapsedTime().asSeconds() >= placeCD;
    }
    
    // 检查将要放置的沙子是否与已经存在的沙子重叠
    static bool checkOverlapping(int placeX)
    {
        for (int i = placeX; i < placeX + blockSize * curShape.w; i++)
            for (int j = 0; j < blockSize * curShape.h; j++)
                if (curShape.data[(i - placeX) / blockSize][j / blockSize] && sand::updatableSand(*sand::sands[i][j]))
                    return true;
        return false;
    }

    void nextPlacement()
    {
        static std::default_random_engine e(time(NULL));
        static std::uniform_int_distribution<int> d1(0, 6), d2(0, 3);
        curShape = shape::shapes[d1(e)];
        curType = nextType;
        nextType = d2(e);
        const int rotate = d2(e);
        for (int i = 0; i < rotate; i++)
            curShape.leftRotate();
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
        nextPlacement();
        source::refreshHints();
        placed = true;
    }
}