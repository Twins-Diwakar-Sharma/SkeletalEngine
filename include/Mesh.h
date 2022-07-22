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
	int noOfIndices;
	void generate(std::vector<float>&, std::vector<unsigned int>&);
	
public:
	Mesh();
	Mesh(std::string);
	~Mesh();
	Mesh(Mesh&);
	Mesh(Mesh&&);
	void createPlane();
	void bind();
	void unbind();
	int indicesSize();
};

#endif