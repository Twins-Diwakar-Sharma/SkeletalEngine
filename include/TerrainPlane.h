#ifndef H_CHHALA_OBJ3CT_H
#define H_CHHALA_OBJ3CT_H

#include "Mathril.h"
class TerrainPlane
{
public:
    TerrainPlane* coarse=nullptr;
    Vec2 position;
    Vec2 step;
    int scale;
    int tesselatedSize;

    TerrainPlane();
    TerrainPlane(TerrainPlane&);
    TerrainPlane(TerrainPlane&&);
    ~TerrainPlane();

    void update(Vec2& dir);
};

#endif