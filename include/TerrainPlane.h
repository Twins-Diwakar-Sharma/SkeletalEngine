#ifndef H_CHHALA_OBJ3CT_H
#define H_CHHALA_OBJ3CT_H

#include "Mathril.h"

class TerrainPlane
{
public:
    Vec2 position;
    Vec2 step;
    int scale;
    int tesselatedSize;

    TerrainPlane();
    TerrainPlane(TerrainPlane&);
    TerrainPlane(TerrainPlane&&);
    ~TerrainPlane();
};

#endif