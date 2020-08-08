#pragma once
#include "Transform.h"
#include "Camera.h"

class Example
{
public:
	Example(Shader* shader, GLFWwindow* window):
		m_shader(shader),
		m_window(window)
	{
		m_camera = new Camera();
		m_transform = new Transform(m_shader);
		m_shader->setFloat("mixValue", 0.2f);

		m_camera->processMouseInput(window);
	}

	void update(float deltaTime) {
		//upDownMix();
		m_camera->processInput(m_window, deltaTime);
		m_transform->setViewMartix(m_camera->getViewMartix());
	}

	void createCueBox() {
		for (int i = 0; i < cubePositions.size(); i++)
		{
			m_transform->setPosition(cubePositions[i]);
			m_transform->updateTransform();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

private:
	Shader* m_shader;
	GLFWwindow* m_window;
	Transform* m_transform;
	Camera* m_camera;

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
	
	float m_mixValue = 0;

	void upDownMix() {
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			m_mixValue -= 0.01;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_mixValue += 0.01;
		}
		m_mixValue = m_mixValue > 1 ? 1 : m_mixValue;
		m_mixValue = m_mixValue < 0 ? 0 : m_mixValue;
		m_shader->setFloat("mixValue", m_mixValue);
	}
};
