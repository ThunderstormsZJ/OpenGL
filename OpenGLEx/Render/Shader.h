#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include "../Utils/ShaderLoader.hpp"

using namespace Utils;

// ��ȡShader��
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void loadVertexShader(const char* vertexPath);
	void loadFragShader(const char* fragmentPath);
	void loadGeometryShader(const char* geometryPath);
	void use();
	void setInt(const std::string &name, float value);
	void setFloat(const std::string &name, float value);
	void setMat(const std::string &name, float* value);
	void setVec3(const std::string& name, const float* value);
	void setVec3(const std::string& name, float x, float y, float z);
	void setBool(const std::string& name, bool value);
private:
	ShaderLoader loader;
	const char* vertexSource;
	const char*  fragmentSource;
	unsigned int shaderProgramID;

	void checkProgramErrors(unsigned int ID);
};

template <class T>
int getArrayLen(T& array)
{
	return (sizeof(array) / sizeof(array[0]));
}

