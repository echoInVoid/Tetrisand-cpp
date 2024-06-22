#include "shape.h"
#include <vector>
using std::vector;

namespace shape
{
    Shape::Shape(vector<vector<bool>> d)
    {
        this->w = d.size();
        this->h = d[0].size();
        this->data = d;
    }

    void Shape::rightRotate()
    {
        vector<vector<bool>> tmp;
        for (int i = 0; i < this->w; i++)
            for (int j = 0; j < this->h; j++)
                tmp[j][this->w - 1 - i] = this->data[i][j];
        std::swap(this->w, this->h);
        this->data = tmp;
    }

    void Shape::leftRotate()
    {
        vector<vector<bool>> tmp;
        for (int i = 0; i < this->w; i++)
            for (int j = 0; j < this->h; j++)
                tmp[this->h - 1 - j][i] = this->data[i][j];
        std::swap(this->w, this->h);
        this->data = tmp;
    }

    Shape shapes[7] = {
        Shape({ // L
            {0, 1},
            {0, 1},
            {1, 1}
        }),
        Shape({ // ·´L
            {1, 0},
            {1, 0},
            {1, 1}
        }),
        Shape({ // I
            {1, 1, 1, 1}
        }),
        Shape({ // O
            {1, 1},
            {1, 1}
        }),
        Shape({ // Z
            {1, 1, 0},
            {0, 1, 1}
        }),
        Shape({ // S
            {0, 1, 1},
            {1, 1, 0}
        }),
        Shape({ // T
            {1, 1, 1},
            {0, 1, 0}
        })
    };
}