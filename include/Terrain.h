#ifndef H_BHOOMI_H
#define H_BHOOMI_H

#include "TerrainMesh.h"
#include "PlatformMesh.h"
#include "RingMesh.h"
#include "TerrainPlane.h"
#include "PlankMesh.h"

class Terrain
{
private:
    int startScale=2;
    int lod=2;
    int startTesselatedSize;
    int noOfRings=2;
   
    std::vector<TerrainPlane*> planes;
    Vec2 distance;
    Vec2 dir;
    
    RingMesh* ringMesh;
    PlatformMesh* platformMesh;
    PlankMesh* plankMesh;
   

public:
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

    void bindPlankMesh();
    int getPlankMeshIndicesSize();

    void unbindMesh();
    TerrainPlane* getPlanes(int);

    int getNoOfRings();

};

#endif