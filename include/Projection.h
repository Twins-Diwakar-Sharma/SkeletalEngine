#ifndef H_PR0J3CT10N_H
#define H_PR0J3CT10N_H

#include "Mathril.h"

namespace proj
{
    extern Mat4 perspective;
    extern float fov;
    extern float near;
    extern float far;

    void setPerspective(float fov, float near, float far, float aspectRatio);
}


#endif