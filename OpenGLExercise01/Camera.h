#pragma once
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Camera
{
public:
	Camera() {
		m_cameraPitch = 0;
		m_cameraYaw = -90;
		m_cameraPos = glm::vec3(0, 0, 3);
		m_worldUp = glm::vec3(0, 1, 0);

		updateVector();
	}

	glm::mat4 getViewMartix() {
		glm::mat4 viewMartix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFont, m_cameraUp);

		return viewMartix;
	}

	void processInput(GLFWwindow* window, float deltaTime) {
		float moveSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_cameraPos += m_cameraFont * moveSpeed;
		}
		
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_cameraPos -= m_cameraFont * moveSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_cameraPos += glm::normalize(glm::cross(m_cameraUp, m_cameraFont)) * moveSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_cameraPos -= glm::normalize(glm::cross(m_cameraUp, m_cameraFont)) * moveSpeed;
		}
	}

	void processMouseInput(GLFWwindow* window) {
		glfwSetWindowUserPointer(window, static_cast<void*>(this));
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ²¶»ñ¹â±ê
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			auto self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
			self->mouseEulerMove(xpos, ypos);
		});
	}

	void mouseEulerMove(double xpos, double ypos) {
		if (m_firstMouse) {
			m_lastMouseX = xpos;
			m_lastMouseY = ypos;
			m_firstMouse = false;
		}

		float xOffset = xpos - m_lastMouseX;
		float yOffset = m_lastMouseY - ypos;

		m_lastMouseX = xpos;
		m_lastMouseY = ypos;

		m_cameraYaw += xOffset * m_mouseMoveSpeed;
		m_cameraPitch += yOffset * m_mouseMoveSpeed;

		updateVector();
	}

	void updateVector() {
		glm::vec3 font;
		font.x = cos(glm::radians(m_cameraPitch)) * cos(glm::radians(m_cameraYaw));
		font.y = sin(glm::radians(m_cameraPitch));
		font.z = cos(glm::radians(m_cameraPitch)) * sin(glm::radians(m_cameraYaw));
		m_cameraFont = glm::normalize(font);
		m_cameraRight = glm::normalize(glm::cross(m_cameraFont, m_worldUp));
		m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFont));
	}
private:
	bool m_firstMouse = true;
	float m_mouseMoveSpeed = 0.02f;
	float m_lastMouseX = WINDOW_WIDTH / 2;
	float m_lastMouseY = WINDOW_HEIGHT / 2;

	float m_cameraPitch = 0;
	float m_cameraYaw = 0;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFont;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;
	glm::vec3 m_worldUp;
};