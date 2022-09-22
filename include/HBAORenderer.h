#ifndef H_HBAO_R3ND3R3R_H
#define H_HBAO_R3ND3R3R_H

#include "Mathril.h"
#include "ShaderProgram.h"
#include "Framebuffer.h"
#include "Mesh.h"
#include "Projection.h"
#include <random>
#include <vector>

class HBAORenderer
{
private:
    ShaderProgram shaderProgram;
    unsigned int noiseTextureID;
    std::vector<Vec3> samples;
public:
    HBAORenderer();
    ~HBAORenderer();
    void render(Mesh& quad, Framebuffer& deferredShadingFramebuffer);

};

#endif