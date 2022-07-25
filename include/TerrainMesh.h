#ifndef H_BH00M1_JALLA_H
#define H_BH00M1_JALLA_H

#include <vector>
#include "glad/glad.h"
#include <iostream>
#include "Debug.h"

class TerrainMesh
{
protected:
	unsigned int vao, vbo, ebo;
    int sizeOfIndices=0;

    virtual void create(std::vector<float>& vertexData, std::vector<unsigned int>& indices);
    void generate(std::vector<float>& vertexData, std::vector<unsigned int>& indices); // creates buffers and assigns sizeOfIndices
public:
    TerrainMesh();
    ~TerrainMesh();
    void bind();
	void unbind();
	int indicesSize();
};


#endif