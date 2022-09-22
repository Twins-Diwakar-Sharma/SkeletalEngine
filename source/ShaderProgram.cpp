#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string name): ShaderProgram(name, NOTHING)
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

ShaderProgram::ShaderProgram(std::string name, int sophistication)
{

	std::string vertexFile(path + name + ".vs");
	std::string fragmentFile(path + name + ".fs");
	programID = glCreateProgram();
	createShader(vertexID, GL_VERTEX_SHADER, vertexFile);
	createShader(fragmentID, GL_FRAGMENT_SHADER, fragmentFile);

	unsigned int geometryID=-1, tessControlID=-1, tessEvalID=-1;

	if (sophistication == GEO)
	{
		std::string geometryFile(path + name + ".gs");
		createShader(geometryID, GL_GEOMETRY_SHADER, geometryFile);
		glAttachShader(programID, geometryID);
	}
	else if (sophistication == TESS)
	{
		std::string tessControlFile(path + name + ".tesc");
		std::string tessEvalFile(path + name + ".tese");
		createShader(tessControlID, GL_TESS_CONTROL_SHADER, tessControlFile);
		createShader(tessEvalID, GL_TESS_EVALUATION_SHADER, tessEvalFile);
		glAttachShader(programID, tessControlID);
		glAttachShader(programID, tessEvalID);
	}
	else if (sophistication == GEOTESS)
	{
		std::string tessComputeFile(path + name + ".tesc");
		std::string tessEvalFile(path + name + ".tese");
		std::string geometryFile(path + name + ".gs");
		createShader(geometryID, GL_GEOMETRY_SHADER, geometryFile);
		createShader(tessControlID, GL_TESS_CONTROL_SHADER, tessComputeFile);
		createShader(tessEvalID, GL_TESS_EVALUATION_SHADER, tessEvalFile);
		glAttachShader(programID, tessControlID);
		glAttachShader(programID, tessEvalID);
		glAttachShader(programID, geometryID);
	}
		 

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	int success;
	char infoLog[256];
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "Failed to link " << name << " \n " << infoLog << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	
	if (sophistication == GEO)
	{
		glDeleteShader(geometryID);
	}
	else if (sophistication == TESS)
	{
		glDeleteShader(tessControlID);
		glDeleteShader(tessEvalID);
	}
	else if (sophistication == GEOTESS)
	{
		glDeleteShader(tessControlID);
		glDeleteShader(tessEvalID);
		glDeleteShader(geometryID);
	}


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

void ShaderProgram::mapCameraUniform(std::string camName)
{
	const char* cUniformSpin = (camName + ".spin").c_str();
	const char* cUniformPos = (camName + ".pos").c_str();
	int spinLoc = glGetUniformLocation(programID, cUniformSpin);
	int posLoc = glGetUniformLocation(programID, cUniformPos);
	uniformMap.insert(std::pair <std::string,int> (camName+".spin", spinLoc));
	uniformMap.insert(std::pair <std::string,int> (camName+".pos", posLoc));
}

void ShaderProgram::mapDirectionalLightUniform(std::string lightName)
{
	const char* cUniformDir = (lightName + ".dir").c_str();
	const char* cUniformPos = (lightName + ".col").c_str();
	int dirLoc = glGetUniformLocation(programID, cUniformDir);
	int posLoc = glGetUniformLocation(programID,cUniformPos);
	uniformMap.insert(std::pair <std::string,int> (lightName + ".dir", dirLoc));
	uniformMap.insert(std::pair <std::string,int> (lightName+".col", posLoc));
}


void ShaderProgram::mapArrayUniform(std::string uniform, int size)
{
	for(int i=0; i<size; i++)
	{
		std::string uniformName = uniform + "[" + std::to_string(i) + "]";
		const char* cUniformName = uniformName.c_str();
		int loc = glGetUniformLocation(programID, cUniformName);
		uniformMap.insert(std::pair <std::string,int> (uniformName, loc));
	}
}

void ShaderProgram::setUniform(std::string uniformName, float x, float y)
{
	glUniform2f(uniformMap[uniformName], x, y);
}

void ShaderProgram::setUniform(std::string uniformName, int value)
{
	glUniform1i(uniformMap[uniformName], value);
}

void ShaderProgram::setUniform(std::string name, Vec2& v)
{
	glUniform2f(uniformMap[name], v[0], v[1]);
}

void ShaderProgram::setUniform(std::string name, Vec3& v)
{
	glUniform3f(uniformMap[name], v[0], v[1], v[2]);
}

void ShaderProgram::setUniform(std::string name, Vec3&& v)
{
	glUniform3f(uniformMap[name], v[0], v[1], v[2]);
}

void ShaderProgram::setUniform(std::string name, Mat4& m)
{	
	glUniformMatrix4fv(uniformMap[name], 1, true, m[0]);
}

void ShaderProgram::setUniform(std::string name, Camera& cam)
{
	std::string spin = name + ".spin";
	std::string pos = name + ".pos";

	glUniform4f(uniformMap[spin],  cam.spin[1], cam.spin[2], cam.spin[3], cam.spin[0]);
	glUniform3f(uniformMap[pos], cam.position[0], cam.position[1], cam.position[2]);	
}

void ShaderProgram::setUniform(std::string name, DirectionalLight& light)
{
	std::string dirName = name + ".dir";
	std::string colName = name + ".col";
	Vec3 dir = light.getDirection();
	Vec3 col = light.getColor();

	glUniform3f(uniformMap[dirName],  dir[0], dir[1], dir[2]);
	glUniform3f(uniformMap[colName], col[0], col[1], col[2]);	
}

void ShaderProgram::setUniform(std::string name, std::vector<Vec3>& kernels)
{
	for(int i=0; i<kernels.size(); i++)
	{
		std::string uniName = name + "[" + std::to_string(i) + "]";
		glUniform3f(uniformMap[uniName], kernels[i][0], kernels[i][1], kernels[i][2]);
	}
}
