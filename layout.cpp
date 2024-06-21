#pragma once

#include "Area.h"
#include "layout.h"

namespace layout
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