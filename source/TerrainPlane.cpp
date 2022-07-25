#include "TerrainPlane.h"

TerrainPlane::TerrainPlane()
{
    LOG("TerrainPlane Def constr");
}

TerrainPlane::TerrainPlane(TerrainPlane& ro)
{
    LOG("TerrainPlane l copy");
    position = ro.position;
    step = ro.step;
    scale = ro.scale;
    tesselatedSize = ro.tesselatedSize;
    coarse = ro.coarse;
}

TerrainPlane::TerrainPlane(TerrainPlane&& ro)
{
    LOG("TerrainPlane R copy");
    position = std::move(ro.position);
    step = std::move(ro.step);
    scale = std::move(ro.scale);
    tesselatedSize = std::move(ro.tesselatedSize);
    coarse = ro.coarse;
    ro.coarse = nullptr;
}

TerrainPlane& TerrainPlane::operator=(TerrainPlane& ro)
{
    LOG("TerrainPlane l =");
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
    ro.coarse = nullptr;

    return *this;
}

TerrainPlane::~TerrainPlane()
{
    LOG("TerrainPlane Dstr"); 
}

void TerrainPlane::update(Vec2& dir)
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

    if(change && coarse)
    {
        coarse->update(dir);
    }
}