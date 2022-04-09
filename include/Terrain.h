#ifndef H_BHOOMI_H
#define H_BHOOMI_H

#include "TerrainMesh.h"
#include "PlatformMesh.h"
#include "RingMesh.h"
#include "TerrainPlane.h"

class Terrain
{
private:
    int startScale=32;
    int lod=32;
    int startTesselatedSize;
    int noOfRings=2;
   
    std::vector<TerrainPlane*> planes;
    Vec2 distance;
public:
 RingMesh* ringMesh;
    PlatformMesh* platformMesh;
    
    Terrain();
    ~Terrain();
    void reconfigure(int startScale,int lod);
    int getStartScale();
    int getLod();

    void update(Vec3& campos);

    void bindPlatformMesh();
    int getPlatformMeshIndicesSize();

    void bindRingMesh();
    int getRingMeshIndicesSize();

    void unbindMesh();
    TerrainPlane* getPlanes(int);

    int getNoOfRings();

};

#endif