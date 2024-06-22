#pragma once

#include <vector>
using std::vector;

namespace shape
{
    class Shape
    {
    public:
        int w=0, h=0; // ��block��
        vector< vector<bool> > data;

        Shape() = default;
        Shape(vector<vector<bool>> d);

        void rightRotate(); // ��������
        void leftRotate(); // ��������
    };

    extern Shape shapes[7];
}