#pragma once
#include <string>
#include "glm.hpp"

struct Vertex {
	glm::vec3 Position; // ��������
	glm::vec3 Normal; // ���㷨����
	glm::vec2 TexCoords; // ��������
};

struct Texture {
	unsigned int Id; // ����ID
	std::string Type; // ��������
	std::string Name; // ��������
	std::string Path; // ����·��
};

struct Material
{
	int Shininess = 2;
};

struct BaseLight {
	glm::vec3 Color = glm::vec3(1.0f);
	bool IsOpen = true;
	float Ambient;
	float Diffuse;
	float Specular;
};

struct PointLight: public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3 Position;

	// ˥��ϵ��
	float Constant = 1.0f; // ������
	float Linear = 0.09f;  // һ����
	float Quadratic = 0.032f; // ������
};

struct DirLight : public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3 Direction;
};

struct SpotLight: public BaseLight
{
	using BaseLight::BaseLight;

	glm::vec3 Position;
	glm::vec3 Direction;
	float CutOffRad; // �۹�ƽǶ�
	float SmoothEdgeIntensity = 5.0f; // ��Ե�ữǿ��

	// ˥��ϵ��
	float Constant = 1.0f; // ������
	float Linear = 0.09f;  // һ����
	float Quadratic = 0.032f; // ������
};