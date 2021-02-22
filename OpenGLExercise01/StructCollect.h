#pragma once
#include <string>

struct ImgTexture {
	std::string ImgPath; // ͼƬ·��
	std::string Name; // shader��Ӧ����
	int Index; // shader��Ӧλ��
	unsigned int Texture; // ͼƬλ��

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

	// ˥��ϵ��
	float Constant = 1.0f; // ������
	float Linear = 0.09f;  // һ����
	float Quadratic = 0.032f; // ������
};

struct DirLight : public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3* Direction;
};