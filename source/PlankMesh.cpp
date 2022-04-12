#include "PlankMesh.h"

void PlankMesh::create()
{
    for(int i=-2; i<=2; i++)
    {
        vertexData.push_back(i); vertexData.push_back(-0.5f);
        vertexData.push_back(i); vertexData.push_back(0.5f);
    }

    for(int i=0; i<4; i++)
    {
        indices.push_back(i*2);
        indices.push_back(i*2 + 2);
        indices.push_back(i*2 + 3);
        indices.push_back(i*2 + 1);
    }
}

PlankMesh::PlankMesh()
{
    create();
    generate();
}

PlankMesh::~PlankMesh()
{

}