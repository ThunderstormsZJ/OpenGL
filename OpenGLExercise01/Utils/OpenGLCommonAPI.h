#pragma once

#include <iostream>
#include "Logger.hpp"
#include <string>

class OpenGLCommonAPI
{
public:
	static void PrintSupportExtensions();
private:
	static std::vector<std::string> g_supportExtensions;
	static void GetSupportExtendsions();
	static std::vector<std::string> GetOpenGLVesionInfo();
};
