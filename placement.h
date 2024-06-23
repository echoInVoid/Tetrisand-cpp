#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "shape.h"

namespace placement
{
    extern shape::Shape curShape; // ��һ�����õ���״
    extern int curType; // ��һ�����õ���ɫ
    extern int nextType; // ����һ�����õ���ɫ
    // ����Ϸ��ʼ�����Ƿ���ù�ɳ��
    // ��ȫ�������ε���Ϸ��ʼʱ����ɫ��ʾ����������ʾ���󣩡�
    // ��������൱��ª��������ʱû���뵽���õ����Ʒ��
    extern bool placed;

    float sinceLastPlacement();
    int getPlacementX(sf::RenderWindow* window);
    void nextPlacement();
    void placeSand(sf::RenderWindow* window); // ����ɳ��
}