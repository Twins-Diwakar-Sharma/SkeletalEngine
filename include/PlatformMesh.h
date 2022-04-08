#ifndef H_CHHAJJA_JALA_H
#define H_CHHAJJA_JALA_H

#include "TerrainMesh.h"

class PlatformMesh : public TerrainMesh
{
protected:
    void create();
public:
    PlatformMesh();
    ~PlatformMesh();
};

#endif