#include "TerrainMesh.h"

void TerrainMesh::generate(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
{
    
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

	sizeOfIndices = indices.size();
    
}

void TerrainMesh::bind()
{
	glBindVertexArray(vao);
}

void TerrainMesh::unbind()
{
	glBindVertexArray(0);
}

int TerrainMesh::indicesSize()
{
	return sizeOfIndices;
}

TerrainMesh::TerrainMesh()
{
}

TerrainMesh::~TerrainMesh()
{
    
}

void TerrainMesh::create(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
{

}