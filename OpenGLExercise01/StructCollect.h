#pragma once
#include <string>

struct ImgTexture {
	std::string ImgPath; // 图片路径
	std::string Name; // shader对应名称
	int Index; // shader对应位置
	unsigned int Texture; // 图片位置
};

struct Material
{
	ImgTexture Diffuse;
	ImgTexture Specular;
	ImgTexture Emission;
	float Shininess;
};

struct Light
{
	glm::vec3* Position;
	glm::vec3 Color;
	float Ambient;
	float Diffuse;
	float Specular;

	Light(){}
	Light(glm::vec3 color, float ambient, float diffuse, float specular):
		Color(color),
		Ambient(ambient),
		Diffuse(diffuse),
		Specular(specular)
	{
	}


	~Light() {
		
	}
};