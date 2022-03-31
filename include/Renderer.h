#ifndef H_R3nD3r3R_H
#define H_R3nD3r3R_H


#include "Mathril.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Projection.h"
#include "Object.h"
#include <vector>

class Renderer
{
private:
    ShaderProgram* shaderProgram;
public:
    Renderer();
    ~Renderer();  
    void render(std::vector<Object*>& objects, Camera* cam, DirectionalLight* sun);
};

#endif