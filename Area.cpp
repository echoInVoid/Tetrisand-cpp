#include "Area.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>

// 获取给定矩形的右下角坐标
static inline sf::Vector2f __getLowerRight(sf::FloatRect rect)
{
    return {
        rect.left + rect.width,
        rect.top + rect.height
    };
}

// 根据给定的左上角和右下角计算矩形的尺寸
static inline sf::Vector2f __getSize(sf::Vector2f upperLeft, sf::Vector2f lowerRight)
{
    return {
        lowerRight.x - upperLeft.x,
        lowerRight.y - upperLeft.y
    };
}

Area::Area(sf::Vector2f pos, sf::Vector2f size)
{
    this->x1 = pos.x;
    this->y1 = pos.y;
    this->x2 = pos.x + size.x;
    this->y2 = pos.y + size.y;
}

Area::Area(float x, float y, float w, float h)
{
    *this = Area(
        { x, y },
        { w, h }
    );
}

sf::Vector2f Area::getPos(sf::Vector2f pos)
{
    return { this->x1 + pos.x, this->y1 + pos.y };
}

sf::FloatRect Area::getOverlap(sf::FloatRect rect)
{
    float right = __getLowerRight(rect).x;
    float bottom = __getLowerRight(rect).y;

    sf::Vector2f upperLeft(
        std::max(this->x1, rect.left),
        std::max(this->y1, rect.top)
    );
    sf::Vector2f size = __getSize(
        upperLeft,
        {
            std::min(this->x1, right),
            std::min(this->y1, bottom)
        }
    );
    return sf::FloatRect(upperLeft, size);
}