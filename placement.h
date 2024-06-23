#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shape.h"

namespace placement
{
    extern shape::Shape curShape; // ��һ�����õ���״
    extern int curType; // ��һ�����õ���ɫ
    //extern int nextType; // ����һ�����õ���ɫ
    extern sf::Clock placeClock;

    int getPlacementX(sf::RenderWindow* window);
    void placeSand(sf::RenderWindow* window); // ����ɳ��
}