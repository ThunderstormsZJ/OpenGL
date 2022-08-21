#pragma once
#include "Camera.h"
#include "Cube.h"
#include "LightCube.hpp"
#include "Model.h"

class Scene
{
public:
	Scene(ImGuiTool& tool)
		:m_tool(tool)
	{
		initEvent();

		//createTextureCueBox();
		//createLightCueBox();
		createCubePanel();
		//createNanosuitModel();
	}

	void createCubePanel() {

		Shader shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");

		auto panel = std::make_shared<Cube>(shader, CubeType::Panel);
		panel->SetPosition(glm::vec3(0));
		panel->SetTexture("Resources/metal.png", "texture1");
		addChild(panel);

		auto box = std::make_shared<Cube>(shader, CubeType::Box, true);
		box->SetPosition(glm::vec3(-1.0f, -0.5f, -1.0f));
		box->SetTexture("Resources/marble.jpg", "texture1");
		addChild(box);
		
		box = std::make_shared<Cube>(shader, CubeType::Box, true);
		box->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
		box->SetTexture("Resources/marble.jpg", "texture1");
		addChild(box);
	}

	void createNanosuitModel() {
		Shader shader("Shader/model_VertextShader.glsl", "Shader/model_FragmentShader.glsl");

		auto model = std::make_shared<Model>("Resources/nanosuit/nanosuit.obj", shader);
		addChild(model);
	}
	void createLightCueBox() {
		Shader shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl");

		// box
		for (int i = 0; i < cubePositions.size(); i++)
		{
			auto box = std::make_shared<Cube>(shader);
			box->SetMaterial(&m_tool.material);
			box->SetPosition(cubePositions[i]);
			box->SetRotate(i * 10, glm::vec3(1, 1, 1));
			box->SetTexture("Resources/container2.png", "material.texture_diffuse1");
			box->SetTexture("Resources/container2_specular.png", "material.texture_specular1");
			addChild(box);
		}
	}
	void createTextureCueBox() {
		// Shader init
		Shader shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");
		shader.setFloat("mixValue", 0.2f);

		for (int i = 0; i < cubePositions.size(); i++)
		{
			auto cube = std::make_shared<Cube>(shader);
			cube->GetShader()->setFloat("mixValue", 0.2f);
			cube->SetPosition(cubePositions[i]);
			cube->SetRotate(i * 10, glm::vec3(1, 1, 1));
			cube->SetTexture("Resources/container.jpg", "texture1");
			cube->SetTexture("Resources/awesomeface.png", "texture2");
			addChild(cube);
		}
	}

	void initEvent() {
		// 监听点光源增加事件
		m_tool.onPointLightChange([=](int count) {
			removeChildrenByTag("lamp");

			std::vector<PointLight>* pointLights = Director::GetInstance().GetPPointLights();
			Shader shader("Shader/light_VertextShader.glsl", "Shader/light_lamp_FragmentShader.glsl");
			for (int i = 0; i < count; i++)
			{
				PointLight* light = &pointLights->at(i);
				auto lamp = std::make_shared<LightCube>(shader);
				lamp->SetScale(0.2f);
				lamp->SetTag("lamp");
				lamp->SetLight(light);
				addChild(lamp);
			}
		});
	}

	// 添加外部建模模型
	void addChild(std::shared_ptr<Node> model) {
		m_childrenModel.push_back(model);
	}

	void removeChildrenByTag(std::string tag) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end();) {
			if ((*begin)->GetTag() == tag) {
				begin = m_childrenModel.erase(begin);
			}
			else {
				++begin;
			}
		}
	}
	std::vector<std::shared_ptr<Node>> getChildrenByTag(std::string tag) {
		std::vector<std::shared_ptr<Node>> children;
		for (const auto &child : m_childrenModel) {
			if (child->GetTag() == tag) {
				children.push_back(child);
			}
		}

		return children;
	}
	std::shared_ptr<Node> getChildByName(std::string name) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++) 
		{
			if ((*begin)->GetName() == name) {
				return (*begin);
			}
		}

		return nullptr;
	}

	void render(float deltaTime) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++)
		{
			(*begin)->Render();
		}
	}
	void update(float delataTime) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++)
		{
			(*begin)->Update(delataTime);
		}
	}
	void destory() {
		// clear 后使用智能指针会自动调用析构函数销毁
		m_childrenModel.clear();
	}

private:
	std::vector<std::shared_ptr<Node>> m_childrenModel;
	ImGuiTool& m_tool;

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
