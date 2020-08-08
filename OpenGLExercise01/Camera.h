#pragma once
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Camera
{
public:
	Camera() {
		
	}

	glm::mat4 getViewMartix() {
		glm::mat4 viewMartix = glm::lookAt(m_carmeraPos, m_carmeraPos + m_carmeraFont, m_carmeraUp);

		return viewMartix;
	}

	void processInput(GLFWwindow* window, float deltaTime) {
		float moveSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_carmeraPos += m_carmeraFont * moveSpeed;
		}
		
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_carmeraPos -= m_carmeraFont * moveSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_carmeraPos += glm::normalize(glm::cross(m_carmeraUp, m_carmeraFont)) * moveSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_carmeraPos -= glm::normalize(glm::cross(m_carmeraUp, m_carmeraFont)) * moveSpeed;
		}
	}

	void processMouseInput(GLFWwindow* window) {
		glfwSetWindowUserPointer(window, static_cast<void*>(this));
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ²¶»ñ¹â±ê
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			auto self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
			glfwSetWindowUserPointer(window, nullptr);

		});
	}

	void mouseEulerMove(double xpos, double ypos) {
		//if (firstMouse) {

		//}

		glm::vec3 font;

		float xOffset = xpos - lastMouseX;
		float yOffset = ypos - lastMouseY;
	}
private:
	bool firstMouse = false;
	float lastMouseX = WINDOW_WIDTH / 2;
	float lastMouseY = WINDOW_HEIGHT / 2;

	glm::vec3 m_carmeraPos = glm::vec3(0, 0, 3);
	glm::vec3 m_carmeraFont = glm::vec3(0, 0, -1);
	glm::vec3 m_carmeraUp = glm::vec3(0, 1, 0);
};