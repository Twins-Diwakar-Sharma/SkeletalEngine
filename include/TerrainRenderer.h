#ifndef H_BH00M1_R3nD3r3R_H
#define H_BH00M1_R3nD3r3R_H


#include "Mathril.h"
#include "ShaderProgram.h"
#include "Projection.h"
#include "RingMesh.h"
#include "PlatformMesh.h"
#include <vector>
#include "Terrain.h"

class TerrainRenderer
{
private:
    ShaderProgram* ringShaderProgram;
public:
    TerrainRenderer();
    ~TerrainRenderer();  
    void render(TerrainMesh* mesh, Camera* cam, int size);
    void render(Terrain* terrain, Camera* cam);
};

#endif