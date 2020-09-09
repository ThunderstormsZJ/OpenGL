#pragma once
#include <string>

struct ImgTexture {
	std::string ImgPath; // ͼƬ·��
	std::string Name; // shader��Ӧ����
	int Index; // shader��Ӧλ��
	unsigned int Texture; // ͼƬλ��
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