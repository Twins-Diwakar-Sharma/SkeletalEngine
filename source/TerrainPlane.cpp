#include "TerrainPlane.h"

TerrainPlane::TerrainPlane()
{}

TerrainPlane::TerrainPlane(TerrainPlane& ro)
{
    position = ro.position;
    step = ro.step;
    scale = ro.scale;
    tesselatedSize = ro.tesselatedSize;
}

TerrainPlane::TerrainPlane(TerrainPlane&& ro)
{
    position = std::move(ro.position);
    step = std::move(ro.step);
    scale = std::move(ro.scale);
    tesselatedSize = std::move(ro.tesselatedSize);
}

TerrainPlane::~TerrainPlane()
{

}