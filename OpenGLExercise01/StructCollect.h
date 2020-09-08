#pragma once
#include <string>

struct ImgTexture {
	std::string imgPath; // 图片路径
	std::string name; // shader对应名称
	int index; // shader对应位置
	unsigned int texture; // 图片位置
};