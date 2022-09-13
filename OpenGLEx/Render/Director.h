#pragma once
#include <GLFW\glfw3.h>
#include "Camera.h"
#include "../Common/Templates.h"
#include "../Common/StructCollect.h"
#include "../Utils/Tools.hpp"

#define NR_POINT_LIGHTS 4

class Scene;
class ImGuiTool;

class Director: public Singleton<Director>
{
public:
	GLFWwindow* Window;
	Camera* MainCamera;
	Scene* CurrentScene;
	ImGuiTool* GuiTool;

	~Director() {}

	DirLight* GetPDirLight() { return &dirLight; }
	SpotLight* GetPSpotLight() { return &spotLight; }
	std::vector<PointLight>* GetPPointLights() { return &pointLights; }

	void Init(GLFWwindow* window, Camera* camera, ImGuiTool* guiTool) {
		this->Window = window;
		this->MainCamera = camera;
		this->GuiTool = guiTool;

		InitLight();
	}

	void SetRunScene(Scene* scene) {
		this->CurrentScene = scene;
	}

	void InitLight() {
		// init PointLight
		for (int i = 0; i < NR_POINT_LIGHTS; i++)
		{
			PointLight light; 
			light.Ambient = 0.05f;
			light.Diffuse = 0.8f;
			light.Specular = 1.0f;
			light.Position = pointLightPositions[i];
			pointLights.push_back(light);
		}

		// init dirLight
		DirLight dirLight;
		dirLight.Ambient = 0.05f;
		dirLight.Diffuse = 0.4f;
		dirLight.Specular = 0.5f;
		dirLight.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		dirLight.IsOpen = true;
		this->dirLight = dirLight;

		// init spotLight
		SpotLight spotLight;
		spotLight.Ambient = 0.0f;
		spotLight.Diffuse = 1.0f;
		spotLight.Specular = 1.0f;
		// 光照计算是在观察空间计算的，所以相机朝向始终为(0,0,-1)
		spotLight.Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		spotLight.CutOffRad = glm::radians(12.0f);
		this->spotLight = spotLight;
	}

private:
	// 光源
	std::vector<PointLight> pointLights;
	DirLight dirLight;
	SpotLight spotLight;

	// 点光源位置
	std::vector<glm::vec3> pointLightPositions = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
};