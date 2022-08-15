#pragma once
#define GLEW_STATIC
//通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，等于是将这个头文件变为一个 .cpp 文件了。
//[Link 2019] 防止无法解析外部符号错误（stb_image.h）
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Utils/ImGuiTool.h"
#include "Render/Scene.h"
#include "Render/Director.h"

class Main
{
public:
private:

};