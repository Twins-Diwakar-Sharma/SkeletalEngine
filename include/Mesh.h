#ifndef JALLA
#define JALLA
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <iostream>

class Mesh
{
protected:
	std::vector<float> vertexData;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo;

	void generate();
	
public:
	Mesh();
	Mesh(std::string);
	~Mesh();
	void createPlane();
	void bind();
	void unbind();
	int indicesSize();
};

#endif