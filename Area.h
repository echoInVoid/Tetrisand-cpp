#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// ����һ�����ι����ࡣ
// �ṩһ����ȾԪ��������䶥������꼴���ɴ˻�֪Ԫ�صľ������꣬�������Ԫ�غ;��ε��غ�����
class Area
{
public:

    float x1, y1, x2, y2;

    Area() = default;
    Area(sf::Vector2f pos, sf::Vector2f size);
    Area(float x, float y, float w, float h);

    // @brief ������������Ͻǵ������������������
    const sf::Vector2f getPos(sf::Vector2f pos);
    // @brief ������������뱾���ε��ص�����
    const sf::FloatRect getOverlap(sf::FloatRect rect);
};

