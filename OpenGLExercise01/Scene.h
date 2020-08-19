#pragma once
#include "Camera.h"
#include "Cube.h"

class Scene
{
public:
	Scene(GLFWwindow* window):
		m_window(window)
	{
		m_camera = new Camera();
		m_camera->processMouseInput(window);
		
		createCueBox();
	}

	void createCueBox() {
		// Shader init
		Shader* shader = new Shader("Shader/VertextShader.glsl", "Shader/FragmentShader.glsl");

		for (int i = 0; i < cubePositions.size(); i++)
		{
			Cube* cube = new Cube(shader);
			cube->setPosition(cubePositions[i]);
			cube->setRotate(i * 10, glm::vec3(1, 1, 1));
			cube->setTexture("Resources/container.jpg", "texture1", 0);
			cube->setTexture("Resources/awesomeface.png", "texture2", 1);
			addChild(cube);
		}
	}

	void addChild(Model* child) {
		m_children.push_back(child);
	}

	void render(float deltaTime) {
		m_camera->processInput(m_window, deltaTime);

		for (auto begin = m_children.begin(); begin != m_children.end(); begin++)
		{
			(*begin)->setViewMartix(m_camera->getViewMartix());
			(*begin)->setProjection(m_camera->getFov());

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
	GLFWwindow* m_window;
	Camera* m_camera;
	std::vector<Model*> m_children;

	// œ‰◊”Œª÷√
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
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
