#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include "Mathril.h"

class ShaderProgram
{
private:
    std::string path = "Inventory/Shaders/";
    std::map<std::string, int> uniformMap;
    unsigned int programID, vertexID, fragmentID;

public:
    ShaderProgram(std::string name);
    void createShader(unsigned int& shaderID, int shaderType, std::string filename);
    void use();
    void unuse();
    void mapUniform(std::string uniform);
    void setUniform(std::string, float, float);
	void setUniform(std::string, int);
	void setUniform(std::string, Vec3&);
	void setUniform(std::string, Vec3&&);
	void setUniform(std::string, Mat4&);
	
};

#endif