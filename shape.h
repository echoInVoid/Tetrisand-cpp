#pragma once

#include <vector>
using std::vector;

namespace shape
{
    class Shape
    {
    public:
        int w=0, h=0; // 以block记
        vector< vector<bool> > data;

        Shape() = default;
        Shape(vector<vector<bool>> d);

        void rightRotate(); // 右旋自身
        void leftRotate(); // 左旋自身
    };

    extern Shape shapes[7];
}