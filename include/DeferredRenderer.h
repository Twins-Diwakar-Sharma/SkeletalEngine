#ifndef H_D3FERR3D_R3ND3R3R_H
#define H_D3FERR3D_R3ND3R3R_H

#include "Mathril.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Framebuffer.h"

class DeferredRenderer
{
private:
    ShaderProgram shaderProgram;
public:
    DeferredRenderer();
    ~DeferredRenderer();  
    void render(Mesh& quad, Framebuffer&);
};

#endif