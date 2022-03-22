#ifndef H_R3nD3r3R_H
#define H_R3nD3r3R_H

#define _USE_MATH_DEFINES
#include <cmath>
#include "Mathril.h"
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "Mesh.h"

namespace proj
{
    extern Mat4 perspective;

    void setPerspective(float fov, float near, float far, float aspectRatio);
}

class Renderer
{
private:
    ShaderProgram* shaderProgram;
public:
    Renderer();
    ~Renderer();
    void render(Mesh* mesh);
};

#endif