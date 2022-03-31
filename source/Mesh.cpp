#include "Mesh.h"



void Mesh::generate()
{
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);

}

Mesh::Mesh()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

Mesh::Mesh(std::string name)
{
	std::string path = "inventory/models/" + name + ".stc";
	std::ifstream ifs(path);
	std::string line;
	
	std::getline(ifs, line);
	std::istringstream iss(line);
	float f;
	while (iss >> f)
		vertexData.push_back(f);

	std::getline(ifs, line);
	std::istringstream iss2(line);
	unsigned int ui;
	while (iss2 >> ui)
		indices.push_back(ui);

	generate();
}

Mesh::~Mesh()
{
}

void Mesh::createPlane()
{
/*	vertexData = {
		// positions          // texture	  // normals
		 0.5f,  0.5f, 0.0f,	  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,// top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,// bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,// bottom left
		-0.5f, 0.5f, 0.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,// top left
	};

	// 0 1 2  0 3 2
	indices = { 0, 1, 2, 3, 0, 2 };
*/
	vertexData = {
		1.0f,	0.0f,	-1.0f,	1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		1.0f,	0.0f,	1.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,	0.0f,	-1.0f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,	0.0f,	1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};

	indices = {
		0,	1,	3,
		0,	3,	2
	};


	generate();

}

void Mesh::bind()
{
	glBindVertexArray(vao);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

int Mesh::indicesSize()
{
	return indices.size();
}
