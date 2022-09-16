#ifndef JALLA
#define JALLA
#include <fstream>
#include <sstream>
#include <vector>
#include "glad/glad.h"
#include <iostream>

class Mesh
{
protected:
	unsigned int vao, vbo, ebo;
	int sizeOfIndices=0;
	void generate(std::vector<float>&, std::vector<unsigned int>&); // creates buffers and assigns sizeOfIndices
	
public:
	Mesh();
	Mesh(std::string);
	~Mesh();
	void createPlane();
	void createPlane2D();
	void createSkybox();
	void bind();
	void unbind();
	int indicesSize();
};

#endif