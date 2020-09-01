#pragma once
#include "Camera.h"
#include "Cube.h"
#include "Lamp.h"
#include "LightCube.h"

class Scene
{
public:
	Scene(WindowContext* context):
		m_context(context)
	{
		m_camera = new Camera();
		m_camera->processMouseInput(context->window);
		m_lamp = new Lamp();
		m_lamp->setColor(&m_context->tool->LightColor);
		addChild(m_lamp);
		
		//createTextureCueBox();
		createLightCueBox();
	}

	void createLightCueBox() {
		ImGuiTool* tool = m_context->tool;
		// box
		Light * light = new Light();
		light->ViewPos = m_camera->getPPos();
		light->Color = m_lamp->getPPColor();
		light->Position = m_lamp->getPPos();

		LightCube* box = new LightCube(m_lamp, light);
		// box->setPosition(glm::vec3(1, 0, -3));
		box->setColor(&tool->ObjectColor);
		addChild(box);
	}

	void createTextureCueBox() {
		// Shader init
		Shader* shader = new Shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");

		for (int i = 0; i < cubePositions.size(); i++)
		{
			Cube* cube = new Cube(shader);
			shader->use();
			shader->setFloat("mixValue", 0.2f);
			cube->setPosition(cubePositions[i]);
			cube->setRotate(i * 10, glm::vec3(1, 1, 1));
			cube->setTexture("Resources/container.jpg", "texture1", 0);
			cube->setTexture("Resources/awesomeface.png", "texture2", 1);
			addChild(cube);
		}
	}

	void addChild(Model* child) {
		child->setCamera(m_camera);
		m_children.push_back(child);
	}

	Model* getChildByName(std::string name) {
		for (auto begin = m_children.begin(); begin != m_children.end(); begin++) 
		{
			if ((*begin)->getName() == name) {
				return (*begin);
			}
		}
	}

	void render(float deltaTime) {
		m_camera->processInput(m_context->window, deltaTime);

		for (auto begin = m_children.begin(); begin != m_children.end(); begin++)
		{
			(*begin)->render();
		}
	}
	void update(float delataTime) {
		for (auto begin = m_children.begin(); begin != m_children.end(); begin++)
		{
			(*begin)->update(delataTime);
		}
	}
	void destory() {
		for (auto begin = m_children.begin();begin!=m_children.end();begin++)
		{
			(*begin)->destroy();
		}
	}

private:
	WindowContext* m_context;
	Camera* m_camera;
	Lamp* m_lamp;
	std::vector<Model*> m_children;

	// œ‰◊”Œª÷√
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
	/*	glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)*/
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
