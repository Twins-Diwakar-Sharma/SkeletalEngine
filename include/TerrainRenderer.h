#ifndef H_BH00M1_R3nD3r3R_H
#define H_BH00M1_R3nD3r3R_H


#include "Mathril.h"
#include "ShaderProgram.h"
#include "Projection.h"
#include "RingMesh.h"
#include "PlatformMesh.h"
#include <vector>
#include "Terrain.h"
#include "PlankMesh.h"

class TerrainRenderer
{
private:
    ShaderProgram* ringShaderProgram;
public:
    TerrainRenderer();
    ~TerrainRenderer();  
    void render(Terrain* terrain, Camera* cam, DirectionalLight* sun);
    
};

#endif