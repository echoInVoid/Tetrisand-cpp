#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shape.h"

namespace placement
{
    extern shape::Shape curShape; // 下一个放置的形状
    extern int curType; // 下一个放置的颜色
    extern int nextType; // 再下一个放置的颜色
    // 自游戏开始以来是否放置过沙子
    // 完全用于屏蔽掉游戏开始时的颜色提示动画（会显示错误）。
    // 这个方法相当丑陋，但我暂时没有想到更好的替代品。
    extern bool placed;

    float sinceLastPlacement();
    int getPlacementX(sf::RenderWindow* window);
    void nextPlacement();
    void placeSand(sf::RenderWindow* window); // 放置沙子
}