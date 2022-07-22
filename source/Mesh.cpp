#include "Mesh.h"



void Mesh::generate(std::vector<float>& vertexData, std::vector<unsigned int>& indices)
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

Mesh::Mesh(Mesh& mesh)
{
	vao = mesh.vao;
	vbo = mesh.vbo;
	ebo = mesh.ebo;
	noOfIndices = mesh.noOfIndices;
}

Mesh::Mesh(Mesh&& mesh)
{
	vao = mesh.vao;
	vbo = mesh.vbo;
	ebo = mesh.ebo;
	noOfIndices = mesh.noOfIndices;
	mesh.vao = 0;
	mesh.vbo = 0;
	mesh.ebo = 0;
	mesh.noOfIndices = 0;
}

Mesh::Mesh()
{

}

Mesh::Mesh(std::string name)
{
	std::cout << "mesh make" << std::endl;
	std::string path = "inventory/models/" + name + ".stc";
	std::ifstream ifs(path, std::ios::binary | std::ios::in);

	int size=0;
	ifs.read((char*)&size, sizeof(int));
	float f=0;
	std::vector<float> vertexData;
	vertexData.reserve(size);
	for(int i=0; i<size; i++)
	{
		ifs.read((char*)&f, sizeof(float));
		vertexData.push_back(f);
	}

	ifs.read((char*)&size, sizeof(int));
	unsigned int ui;
	std::vector<unsigned int> indices;
	indices.reserve(size);
	for(int i=0; i<size; i++)
	{
		ifs.read((char*)&ui, sizeof(unsigned int));
		indices.push_back(ui);
	}
	noOfIndices = indices.size();

	generate(vertexData,indices);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
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
	std::vector<float> vertexData = {
		1.0f,	0.0f,	-1.0f,	1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		1.0f,	0.0f,	1.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,	0.0f,	-1.0f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,	0.0f,	1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};

	std::vector<unsigned int> indices = {
		0,	1,	3,
		0,	3,	2
	};

	noOfIndices = 6;

	generate(vertexData, indices);
	

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
	return noOfIndices;
}
