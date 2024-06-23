#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shape.h"

namespace placement
{
    extern shape::Shape curShape; // 下一个放置的形状
    extern int curType; // 下一个放置的颜色
    //extern int nextType; // 再下一个放置的颜色
    extern sf::Clock placeClock;

    int getPlacementX(sf::RenderWindow* window);
    void placeSand(sf::RenderWindow* window); // 放置沙子
}