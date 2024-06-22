#pragma once

#include "layout.h"

namespace render
{
    const int windowW=600, windowH=800;
    const int fps=30;
    const int sandSize=4; // 单颗沙粒渲染时的边长
}

namespace sand
{
    const int sandListW = (int)layout::sand.getSize().x / render::sandSize;
    const int sandListH = (int)layout::sand.getSize().y / render::sandSize;
}