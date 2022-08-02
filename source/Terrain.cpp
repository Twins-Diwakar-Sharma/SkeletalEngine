#include "Terrain.h"

Terrain::Terrain()
{
    
    for(int i=0; i<noOfRings+1; i++)
    {
        planes.push_back(TerrainPlane());
        if(i>0)
        {
            planes[i-1].coarse = i;
        }
    }
    startTesselatedSize = startScale/lod;


    int scale = startScale;
    int tessSize = startTesselatedSize;
    for(int i=0; i<noOfRings+1; i++)
    {
        planes[i].scale = scale;
        planes[i].tesselatedSize = tessSize;
        scale *= 2;
        tessSize *= 2;
    }    
}

Terrain::~Terrain()
{

}

void Terrain::reconfigure(int scale, int lod)
{
    this->lod = lod;
    startScale = scale;
    startTesselatedSize = startScale/lod;
    int tessSize = startTesselatedSize;
    for(int i=0; i<noOfRings+1; i++)
    {
        planes[i].scale = scale;
        planes[i].tesselatedSize = tessSize;
        scale = scale * 2;
        tessSize = tessSize * 2;
    }  
}

int Terrain::getStartScale()
{
    return startScale;
}

int Terrain::getLod()
{
    return lod;
}

void Terrain::update(Vec3& campos)
{
    distance[0] = campos[0] - planes[0].position[0];
    distance[1] = campos[2] - planes[0].position[1]; 

    int limit = planes[0].tesselatedSize/2;

    distance[0] > limit ? dir[0] = 1 : (distance[0] < -limit ? dir[0] = -1 : dir[0] = 0);  
    distance[1] > limit ? dir[1] = 1 : (distance[1] < -limit ? dir[1] = -1 : dir[1] = 0);
    
    bool updateNext = true;
    for(int i=0; i<planes.size() && updateNext; i++)
    {
        updateNext = planes[i].update_ifStep2(dir);
    }

}

void Terrain::bindPlatformMesh()
{
    platformMesh.bind();
}
int Terrain::getPlatformMeshIndicesSize()
{
    return platformMesh.indicesSize();
}


void Terrain::bindRingMesh()
{
    ringMesh.bind();
}

int Terrain::getRingMeshIndicesSize()
{
    return ringMesh.indicesSize();
}

void Terrain::unbindMesh()
{
    glBindVertexArray(0);
}

TerrainPlane& Terrain::getPlanes(int i)
{
    return planes[i];
}

int Terrain::getNoOfRings()
{
    return noOfRings;
}
 