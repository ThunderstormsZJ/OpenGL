#pragma once
#include <string>

struct ImgTexture {
	std::string ImgPath; // 图片路径
	std::string Name; // shader对应名称
	int Index; // shader对应位置
	unsigned int Texture; // 图片位置

	ImgTexture() {}
	ImgTexture(std::string imgPath, std::string name, int index) :
		ImgPath(imgPath),
		Name(name),
		Index(index)
	{
	}


	~ImgTexture() {

	}
};

struct Material
{
	ImgTexture Diffuse;
	ImgTexture Specular;
	ImgTexture Emission;
	int Shininess;

	Material() {}
	Material(int shininess) :
		Shininess(shininess)
	{
	}


	~Material() {

	}
};

struct BaseLight {
	glm::vec3* Color;
	bool IsOpen;
	float Ambient;
	float Diffuse;
	float Specular;

	BaseLight(glm::vec3* color, float ambient, float diffuse, float specular):
		Color(color),
		Ambient(ambient),
		Diffuse(diffuse),
		Specular(specular),
		IsOpen(true)
	{
	}
	
	~BaseLight(){}
};

struct PointLight: public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3* Position;

	// 衰减系数
	float Constant = 1.0f; // 常数项
	float Linear = 0.09f;  // 一次项
	float Quadratic = 0.032f; // 二次项
};

struct DirLight : public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3* Direction;
};