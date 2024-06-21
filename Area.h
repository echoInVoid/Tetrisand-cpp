#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// ����һ�����ι����ࡣ
// �ṩһ����ȾԪ��������䶥������꼴���ɴ˻�֪Ԫ�صľ������꣬�������Ԫ�غ;��ε��غ�����
class Area
{
    float x1, y1, x2, y2;

    Area() = default;
    Area(sf::Vector2f pos, sf::Vector2f size);
    Area(float x, float y, float w, float h);

    // @brief ������������Ͻǵ������������������
    sf::Vector2f getPos(sf::Vector2f pos);
    // @brief ������������뱾���ε��ص�����
    sf::FloatRect getOverlap(sf::FloatRect rect);
};

