#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// 这是一个矩形工具类。
// 提供一个渲染元素相对于其顶点的坐标即可由此获知元素的绝对坐标，并计算该元素和矩形的重合区域。
class Area
{
public:

    float x1, y1, x2, y2;

    Area() = default;
    Area(sf::Vector2f pos, sf::Vector2f size);
    Area(float x, float y, float w, float h);

    // @brief 根据与矩形左上角的相对坐标计算绝对坐标
    const sf::Vector2f getPos(sf::Vector2f pos);
    // @brief 计算给定矩形与本矩形的重叠部分
    const sf::FloatRect getOverlap(sf::FloatRect rect);
};

