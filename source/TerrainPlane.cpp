#include "TerrainPlane.h"

TerrainPlane::TerrainPlane()
{
}

TerrainPlane::TerrainPlane(TerrainPlane& ro)
{
    position = ro.position;
    step = ro.step;
    scale = ro.scale;
    tesselatedSize = ro.tesselatedSize;
    coarse = ro.coarse;
}

TerrainPlane::TerrainPlane(TerrainPlane&& ro)
{
    position = std::move(ro.position);
    step = std::move(ro.step);
    scale = std::move(ro.scale);
    tesselatedSize = std::move(ro.tesselatedSize);
    coarse = ro.coarse;
}

TerrainPlane& TerrainPlane::operator=(TerrainPlane& ro)
{
    if(this == &ro)
        return *this;
    position = ro.position;
    step = ro.step;
    scale = ro.scale;
    tesselatedSize = ro.tesselatedSize;
    coarse = ro.coarse;

    return *this;
}

TerrainPlane& TerrainPlane::operator=(TerrainPlane&& ro)
{
    LOG("TerrainPlane r=");
    position = std::move(ro.position);
    step = std::move(ro.step);
    scale = std::move(ro.scale);
    tesselatedSize = std::move(ro.tesselatedSize);
    coarse = ro.coarse;
 

    return *this;
}

TerrainPlane::~TerrainPlane()
{
}

bool TerrainPlane::update_ifStep2(Vec2& dir)
{
    step = step + dir;
    position = position + tesselatedSize*dir; 

    bool change = false;
    dir[0] = 0;
    dir[1] = 0;
    if(step[0] >= 2)
    {
        step[0] = 0;
        change = true;
        dir[0] = 1;
    }
    else if(step[0] <= -2)
    {
        step[0] = 0;
        change = true;
        dir[0] = -1;
    }

    if(step[1] >= 2)
    {
        step[1] = 0;
        change = true;
        dir[1] = 1;
    }
    else if(step[1] <= -2)
    {
        step[1] = 0;
        change = true;
        dir[1] = -1;
    }

   return change;
}