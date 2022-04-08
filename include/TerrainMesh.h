#ifndef H_BH00M1_JALLA_H
#define H_BH00M1_JALLA_H

#include <vector>
#include "glad/glad.h"
#include <iostream>

class TerrainMesh
{
protected:
    std::vector<float> vertexData;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo;

    virtual void create();
    void generate();
public:
    TerrainMesh();
    ~TerrainMesh();
    void bind();
	void unbind();
	int indicesSize();
};


#endif