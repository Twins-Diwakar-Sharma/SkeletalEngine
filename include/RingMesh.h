#ifndef CHHALLA_JALA
#define CHHALLA_JALA

#include <vector>
#include "glad/glad.h"
#include <iostream>

class RingMesh
{
protected:
    std::vector<float> vertexData;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo;

    void generate();
public:
    RingMesh();
    ~RingMesh();
    void bind();
	void unbind();
	int indicesSize();
};

#endif