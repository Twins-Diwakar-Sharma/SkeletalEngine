#ifndef H_CHHALA_OBJ3CT_H
#define H_CHHALA_OBJ3CT_H

#include "Mathril.h"
#include "Debug.h"
#include "vector"
class TerrainPlane
{
public:
    int coarse = -1;

    Vec2 position;
    Vec2 step;
    int scale;
    int tesselatedSize;

    TerrainPlane();
    TerrainPlane(TerrainPlane&);
    TerrainPlane(TerrainPlane&&);
    ~TerrainPlane();

    TerrainPlane& operator=(TerrainPlane&);
    TerrainPlane& operator=(TerrainPlane&&);

    bool update_ifStep2(Vec2& dir);
};

#endif