#ifndef H_R3nD3r3R_H
#define H_R3nD3r3R_H


#include "Mathril.h"
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Projection.h"
#include "Object.h"

class Renderer
{
private:
    ShaderProgram* shaderProgram;
public:
    Renderer();
    ~Renderer();  
    void render(Object* object, Camera* cam);
};

#endif