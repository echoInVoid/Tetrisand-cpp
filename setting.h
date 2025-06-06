#pragma once

#include "layout.h"
#include <algorithm>
#include <cmath>

namespace render
{
    const int windowW = 600, windowH = 800;
    const int fps = 30;
    const int sandSize = 4; // ����ɳ����Ⱦʱ�ı߳�
    const int hintBlockSize = 6 * sandSize; // ��ʾ������ı߳�
}

namespace sand
{
    const int sandListW = (int)round(layout::sand.getSize().x / render::sandSize);
    const int sandListH = (int)round(layout::sand.getSize().y / render::sandSize);
    const int failLine = sandListH * 0.1;
}

namespace update
{
    const int tps = 20;
}

namespace placement
{
    const int blockSize = 10; // ��״�еĵ�����ı߳�����ɳ����
    const int placeCD = 1; // ����CD�������
}