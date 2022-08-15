#include "Shader.h"
#include "Utils/ShaderLoader.hpp"

using namespace std;
using namespace Utils;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	GLuint vertexShader, fragmentShader;

	ShaderLoader loader;
	loader.load(vertexPath);
	vertexShader = loader.compile(GL_VERTEX_SHADER);	
	
	loader.load(fragmentPath);
	fragmentShader = loader.compile(GL_FRAGMENT_SHADER);

	try
	{
		// link
		shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShader);
		glAttachShader(shaderProgramID, fragmentShader);
		glLinkProgram(shaderProgramID);
		checkProgramErrors(shaderProgramID);

		// delete
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (const std::exception& exc)
	{
		printf(exc.what());
	}
}

// 检测编译错误
void Shader::checkProgramErrors(unsigned int ID) {
	int success;
	char infoLog[512];

	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(ID, getArrayLen(infoLog), NULL, infoLog);
		cout << "shader compile error: " << infoLog << endl;
	}
}

void Shader::use() {
	glUseProgram(shaderProgramID);
}

void Shader::setInt(const std::string & name, float value)
{
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string & name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

void Shader::setMat(const std::string & name, float* value)
{
	// 参数1：uniform的位置值
	// 参数2：矩阵的个数
	// 参数3：是否矩阵置换，交换矩阵的行列，OpenGL默认的是列主序
	// 参数4：矩阵的数据
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, value);
}

void Shader::setVec3(const std::string& name, const float* value)
{
	glUniform3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z);
}

void Shader::setBool(const std::string& name, bool value)
{
	setInt(name, value ? 1 : 0);
}


