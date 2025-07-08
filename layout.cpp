#pragma once

#include "Area.h"
#include "layout.h"

namespace layout
{
    namespace start
    {
        Area title({ 96,72 }, { 408,156 });
        // 235 * 45
        Area mode({ 183,280 }, { 235,250 });
        Area score({ 102,650 }, { 395,45 });
    }

    namespace inGame
    {
        // 计分板
        Area info({ 48,32 }, { 504,112 });
        // 沙子区域
        Area sand({ 44,192 }, { 340,560 });
        // 形状提示
        Area shape({ 424,212 }, { 116,116 });
        // 颜色提示
        Area color({ 456,540 }, { 52,108 });
    }
}