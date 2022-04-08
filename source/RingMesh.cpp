#include "RingMesh.h"

void RingMesh::create()
{
    std::cout << "ring mesh create" << std::endl;
    float x = -2, z = -2;
    
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(x+j == 0 && z == 0)
                continue;
            vertexData.push_back(x+j);
            vertexData.push_back(z);
        }
        z++;
    }


    // indices
    float fours[] = {0,1,6,5};
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            indices.push_back(fours[j] + i);
        }
    }

    indices.push_back(5); indices.push_back(6); indices.push_back(11); indices.push_back(10);
    indices.push_back(8); indices.push_back(9); indices.push_back(13); indices.push_back(12);

    indices.push_back(10); indices.push_back(11); indices.push_back(15); indices.push_back(14);
    indices.push_back(12); indices.push_back(13); indices.push_back(18); indices.push_back(17);

    fours[0] = 14; fours[1] = 15; fours[2] = 20; fours[3] = 19;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            indices.push_back(fours[j] + i);
        }
    }

}

RingMesh::RingMesh()
{
    create();
    generate();
}

RingMesh::~RingMesh()
{
    
}
