#ifndef H_L16HT_R3ND3R3R_H
#define H_L16HT_R3ND3R3R_H

#include "Mathril.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Framebuffer.h"
#include "Light.h"
#include "Camera.h"

class LightRenderer
{
private:
    ShaderProgram shaderProgram;
public:
    LightRenderer();
    ~LightRenderer();  
    void render(Mesh& quad, Framebuffer& fb, Framebuffer& ao, DirectionalLight& sun, Camera& cam);
};

#endif