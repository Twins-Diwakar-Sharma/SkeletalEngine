#ifndef H_R3nD3r3R_H
#define H_R3nD3r3R_H

//#include "Shader.h"
//#include "Mesh.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include "Mathril.h"
#include <glad/glad.h>

namespace proj
{
    extern Mat4 perspective;

    void setPerspective(float fov, float near, float far, float aspectRatio);
}

class Renderer
{
private:
    //Shader* shader;
public:
    Renderer();
    ~Renderer();
    void render(/*Mesh* mesh, */ );
};

#endif