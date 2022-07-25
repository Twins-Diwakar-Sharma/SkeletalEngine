#include "PlatformMesh.h"

void PlatformMesh::create(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
{
    LOG("Platform mesh create");
    float x = -2, z = -2;
    
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            vertexData.push_back(x+j);
            vertexData.push_back(z);

        }
        z++;
    }


    // indices
    float fours[] = {0,1,6,5};

    for(int a=0; a<4; a++)
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                indices.push_back(a*5 + fours[j] + i); 
            }
        }
    }
 
}

PlatformMesh::PlatformMesh()
{
    std::vector<float> vertexData;
    std::vector<unsigned int> indices;
    create(vertexData, indices);
    generate(vertexData, indices);
}

PlatformMesh::~PlatformMesh()
{

}

