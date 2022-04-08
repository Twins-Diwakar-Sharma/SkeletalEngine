#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <string>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <iostream>
#include <map>
#include "Mathril.h"
#include "Camera.h"
#include "Light.h"

#define NOTHING 0
#define GEO 1
#define TESS 2
#define GEOTESS 3

class ShaderProgram
{
private:
    std::string path = "inventory/shaders/";
    std::map<std::string, int> uniformMap;
    unsigned int programID, vertexID, fragmentID;

public:
    ShaderProgram(std::string name);
    ShaderProgram(std::string name, int sophistication);
    ~ShaderProgram();
    void createShader(unsigned int& shaderID, int shaderType, std::string filename);
    void use();
    void unuse();
    void mapUniform(std::string uniform);
    void mapCameraUniform(std::string uniform);
    void mapDirectionalLightUniform(std::string uniform);

    void setUniform(std::string, float, float);
	void setUniform(std::string, int);
    void setUniform(std::string, Vec2&);
	void setUniform(std::string, Vec3&);
	void setUniform(std::string, Vec3&&);
	void setUniform(std::string, Mat4&);
    void setUniform(std::string name, Camera& cam);
    void setUniform(std::string name, DirectionalLight& light);
	
};

#endif