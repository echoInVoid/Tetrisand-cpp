#pragma once

#include "layout.h"
#include <algorithm>

namespace render
{
    const int windowW = 600, windowH = 800;
    const int fps = 30;
    const int sandSize = 4; // 单颗沙粒渲染时的边长
    const int hintBlockSize = 6 * sandSize; // 提示区方块的边长
}

namespace sand
{
    const int sandListW = (int)round(layout::sand.getSize().x / render::sandSize);
    const int sandListH = (int)round(layout::sand.getSize().y / render::sandSize);
}

namespace update
{
    const int tps = 20;
}

namespace placement
{
    const int blockSize = 10; // 形状中的单个块的边长，以沙粒计
}