#ifndef H_5KYB0X_R3ND3R3R_H
#define H_5KYB0X_R3ND3R3R_H

#include "Mathril.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "Projection.h"
#include <vector>

class SkyboxRenderer
{
private:
    ShaderProgram shaderProgram;
    Mesh skyboxMesh;
public:
    SkyboxRenderer();
    ~SkyboxRenderer();
    void render(Texture& skyboxTexture, Camera& cam);

};

#endif