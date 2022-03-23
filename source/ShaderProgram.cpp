#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string name)
{
    std::string vertexFile(path + name + ".vs");
    std::string fragmentFile(path + name + ".fs");
    programID = glCreateProgram();
    createShader(vertexID, GL_VERTEX_SHADER, vertexFile);
    createShader(fragmentID, GL_FRAGMENT_SHADER, fragmentFile);
    glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void ShaderProgram::createShader(unsigned int& shaderID, int shaderType, std::string filename)
{
	std::ifstream file(filename);
	if(file.bad())
	{
		std::cerr << filename << " not found " << std::endl;
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string shaderCode = buffer.str();
	buffer.clear();
	file.close();

	shaderID = glCreateShader(shaderType);
	const char* cshaderCode = shaderCode.c_str();
	glShaderSource(shaderID, 1, &cshaderCode, NULL);
	glCompileShader(shaderID);

	int success;
	char infoLog[256];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 256, NULL, infoLog);
		std::cerr << "Failed to compile " << filename << " \n " << infoLog << std::endl;
	}

}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

void ShaderProgram::mapUniform(std::string uniformName)
{
	const char* cUniform = uniformName.c_str();
	int uniformLoc = glGetUniformLocation(programID, cUniform);
	uniformMap.insert(std::pair <std::string,int> (uniformName, uniformLoc));
}

void ShaderProgram::setUniform(std::string uniformName, float x, float y)
{
	int loc = uniformMap[uniformName];
	glUniform2f(loc, x, y);
}

void ShaderProgram::setUniform(std::string uniformName, int value)
{
	int uniformLoc = uniformMap[uniformName];
	glUniform1i(uniformLoc, value);
}

void ShaderProgram::setUniform(std::string name, Vec3& v)
{
	int loc = uniformMap[name];
	glUniform3f(loc, v[0], v[1], v[2]);
}

void ShaderProgram::setUniform(std::string name, Vec3&& v)
{
	int loc = uniformMap[name];
	glUniform3f(loc, v[0], v[1], v[2]);

}

void ShaderProgram::setUniform(std::string name, Mat4& m)
{
	int loc = uniformMap[name];
	
	glUniformMatrix4fv(loc, 1, true, m[0]);
}
