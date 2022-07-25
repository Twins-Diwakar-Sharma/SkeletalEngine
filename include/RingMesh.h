#ifndef CHHALLA_JALA
#define CHHALLA_JALA

#include "TerrainMesh.h"

class RingMesh : public TerrainMesh
{
protected:
    void create(std::vector<float>& vertexData, std::vector<unsigned int>& indices);
public:
    RingMesh();
    ~RingMesh();

};

#endif