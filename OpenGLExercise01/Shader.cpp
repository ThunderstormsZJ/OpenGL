#include "Shader.h"

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSSream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("open file fail");
		}
		// fstream --> stringstream
		vertexSSream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		// stringstream --> char
		string vertexString = vertexSSream.str();
		string fragmentString = fragmentSStream.str();
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		// complie
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");

		// link
		shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShader);
		glAttachShader(shaderProgramID, fragmentShader);
		glLinkProgram(shaderProgramID);
		checkCompileErrors(shaderProgramID, "PROGRAM");

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
void Shader::checkCompileErrors(unsigned int ID, std::string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(ID, getArrayLen(infoLog), NULL, infoLog);
			cout << "shader compile error: " << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(ID, getArrayLen(infoLog), NULL, infoLog);
			cout << "program linking error: " << infoLog << endl;
		}
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

