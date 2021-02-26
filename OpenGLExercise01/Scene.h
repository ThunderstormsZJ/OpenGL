#pragma once
#include "Camera.h"
#include "Cube.h"
#include "Lamp.h"
#include "LightCube.h"
#include "Model.h"

class Scene
{
public:
	Scene(WindowContext* context):
		m_context(context)
	{
		m_camera = new Camera();
		m_camera->processMouseInput(context->window);
		
		createNanosuitModel();
		//createTextureCueBox();
		//createLightCueBox();
	}

	void createNanosuitModel() {
		Shader shader("Shader/model_VertextShader.glsl", "Shader/model_FragmentShader.glsl");
		Model model( "Resources/nanosuit/nanosuit.obj", shader, m_camera);

		addModel(model);
	}
	void createLightCueBox() {
		ImGuiTool* tool = m_context->tool;

		// light
		DirLight& dirLight = tool->dirLight;
		dirLight.IsOpen = false;
		dirLight.Direction = new glm::vec3(-0.2f, -1.0f, -0.3f);

		SpotLight& spotLight = tool->spotLight;
		spotLight.IsOpen = false;
		spotLight.Position = m_camera->getPPos();
		// 光照计算是在观察空间计算的，所以相机朝向始终为(0,0,-1)
		spotLight.Direction = new glm::vec3(0.0f, 0.0f, -1.0f); 
		spotLight.CutOffRad = glm::radians(12.0f);

		tool->onPointLightChange([=](int count) {
			removeChildrenByTag("lamp");
			for (int i = 0; i < count; i++)
			{
				PointLight* light = m_context->tool->pointLights[i];
				Lamp* lamp = new Lamp();
				lamp->setTag("lamp");
				lamp->setColor(light->Color);
				lamp->setPosition(light->Position);
				addTransformModel(lamp);
			}
		});


		// material
		Material& material = tool->material;
		material.Diffuse = ImgTexture("Resources/container2.png", "material.diffuse", 0);
		material.Specular = ImgTexture("Resources/container2_specular.png", "material.specular", 1);
		material.Emission = ImgTexture("", "material.emission", 2);

		// box
		for (int i = 0; i < cubePositions.size(); i++)
		{
			LightCube* box = new LightCube(m_context, &material);
			box->setPosition(&cubePositions[i]);
			box->setRotate(i * 10, glm::vec3(1, 1, 1));
			addTransformModel(box);
		}
	}
	void createTextureCueBox() {
		// Shader init
		Shader* shader = new Shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");

		for (int i = 0; i < cubePositions.size(); i++)
		{
			Cube* cube = new Cube(shader);
			shader->use();
			shader->setFloat("mixValue", 0.2f);
			cube->setPosition(&cubePositions[i]);
			cube->setRotate(i * 10, glm::vec3(1, 1, 1));
			cube->setTexture("Resources/container.jpg", "texture1", 0);
			cube->setTexture("Resources/awesomeface.png", "texture2", 1);
			addTransformModel(cube);
		}
	}

	// 自定义的模型(箱子)
	void addTransformModel(TransformModel* child) {
		child->setCamera(m_camera);
		m_childrenTModel.push_back(child);
	}
	// 添加外部建模模型
	void addModel(Model &model) {
		m_childrenModel.push_back(model);
	}

	void removeChildrenByTag(std::string tag) {
		for (auto begin = m_childrenTModel.begin(); begin != m_childrenTModel.end();) {
			if ((*begin)->getTag() == tag) {
				delete *begin;
				begin = m_childrenTModel.erase(begin);
			}
			else {
				++begin;
			}
		}
	}
	std::vector<TransformModel*> getChildrenByTag(std::string tag) {
		std::vector<TransformModel*> children;
		for (const auto &child : m_childrenTModel) {
			if (child->getTag() == tag) {
				children.push_back(child);
			}
		}

		return children;
	}
	TransformModel* getChildByName(std::string name) {
		for (auto begin = m_childrenTModel.begin(); begin != m_childrenTModel.end(); begin++) 
		{
			if ((*begin)->getName() == name) {
				return (*begin);
			}
		}
	}

	void render(float deltaTime) {
		m_camera->processInput(m_context->window, deltaTime);

		for (auto begin = m_childrenTModel.begin(); begin != m_childrenTModel.end(); begin++)
		{
			(*begin)->render();
		}		
		
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++)
		{
			(*begin).Render();
		}
	}
	void update(float delataTime) {
		for (auto begin = m_childrenTModel.begin(); begin != m_childrenTModel.end(); begin++)
		{
			(*begin)->update(delataTime);
		}
	}
	void destory() {
		for (auto begin = m_childrenTModel.begin();begin!=m_childrenTModel.end();begin++)
		{
			(*begin)->destroy();
		}
	}

private:
	WindowContext* m_context;
	Camera* m_camera;
	std::vector<TransformModel*> m_childrenTModel;
	std::vector<Model> m_childrenModel;

	// 箱子位置
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f,  0.0f,  5.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	//float m_mixValue = 0;

	//void upDownMix() {
	//	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	//		m_mixValue -= 0.01;
	//	}
	//	else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	//	{
	//		m_mixValue += 0.01;
	//	}
	//	m_mixValue = m_mixValue > 1 ? 1 : m_mixValue;
	//	m_mixValue = m_mixValue < 0 ? 0 : m_mixValue;
	//	m_shader->setFloat("mixValue", m_mixValue);
	//}
};
