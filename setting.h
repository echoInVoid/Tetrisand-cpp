#pragma once

#include "layout.h"

namespace render
{
    const int windowW=600, windowH=800;
    const int fps=30;
    const int sandSize=4; // ����ɳ����Ⱦʱ�ı߳�
}

namespace sand
{
    const int sandListW = (int)layout::sand.getSize().x / render::sandSize;
    const int sandListH = (int)layout::sand.getSize().y / render::sandSize;
}