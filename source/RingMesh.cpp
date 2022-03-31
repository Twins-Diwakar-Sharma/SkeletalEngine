#include "RingMesh.h"

void RingMesh::generate()
{
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
        z = z+1;
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

    glPatchParameteri(GL_PATCH_VERTICES, 4);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
    
}

void RingMesh::bind()
{
	glBindVertexArray(vao);
}

void RingMesh::unbind()
{
	glBindVertexArray(0);
}

int RingMesh::indicesSize()
{
	return indices.size();
}

RingMesh::RingMesh()
{
    generate();
}

RingMesh::~RingMesh()
{
    
}
