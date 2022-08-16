#pragma once
#include <string>
#include "glm.hpp"

struct Vertex {
	glm::vec3 Position; // 顶点坐标
	glm::vec3 Normal; // 顶点法向量
	glm::vec2 TexCoords; // 纹理坐标
};

struct Texture {
	unsigned int Id; // 纹理ID
	std::string Type; // 纹理类型
	std::string Name; // 纹理名称
	std::string Path; // 纹理路径
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

	// 衰减系数
	float Constant = 1.0f; // 常数项
	float Linear = 0.09f;  // 一次项
	float Quadratic = 0.032f; // 二次项
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
	float CutOffRad; // 聚光灯角度
	float SmoothEdgeIntensity = 5.0f; // 边缘柔化强度

	// 衰减系数
	float Constant = 1.0f; // 常数项
	float Linear = 0.09f;  // 一次项
	float Quadratic = 0.032f; // 二次项
};