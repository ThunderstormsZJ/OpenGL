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
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// ∂¡»°Shaderµµ
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setInt(const std::string &name, float value);
	void setFloat(const std::string &name, float value);
	void setMat(const std::string &name, float* value);
private:
	const char* vertexSource;
	const char*  fragmentSource;
	unsigned int shaderProgramID;

	void checkCompileErrors(unsigned int ID, std::string type);
};

template <class T>
int getArrayLen(T& array)
{
	return (sizeof(array) / sizeof(array[0]));
}

