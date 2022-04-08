#ifndef H_BHOOMI_H
#define H_BHOOMI_H

#include "TerrainMesh.h"
#include "PlatformMesh.h"
#include "RingMesh.h"
#include "RingObject.h"

class Terrain
{
private:
    int startScale=32;
    int lod=32;
    int startTesselatedSize;
    int noOfRings;
   
    std::vector<RingObject*> planes;
    Vec2 distance;
public:
 RingMesh* ringMesh;
    PlatformMesh* platformMesh;
    
    Terrain(int noOfRings);
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
    RingObject* getPlanes(int);

    int getNoOfRings();

};

#endif