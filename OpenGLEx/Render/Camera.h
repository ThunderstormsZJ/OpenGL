#pragma once
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Camera
{
public:
	Camera() {
		m_cameraPitch = 0;
		m_cameraYaw = -90;
		m_cameraPos = glm::vec3(0, 0, 30);
		m_worldUp = glm::vec3(0, 1, 0);
		m_cameraFov = 45.0f;

		updateVector();
	}

	float getFov() { return m_cameraFov; }
	glm::vec3 getPos() { return m_cameraPos; }
	glm::vec3 * getPPos() { return &m_cameraPos; }
	glm::vec3 * getPFont() { return &m_cameraFont; }

	glm::mat4 getViewMartix() {
		glm::mat4 viewMartix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFont, m_cameraUp);

		return viewMartix;
	}

	// ASDA上下左右操作
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

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			//glfwSetWindowShouldClose(window, true);
			openMouseOperate(window, false);
		}

	}

	void processMouseInput(GLFWwindow* window) {
		glfwSetWindowUserPointer(window, static_cast<void*>(this));

		// 点击操作
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			auto self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS & mods == GLFW_MOD_CONTROL) switch (button)
			{
			case GLFW_MOUSE_BUTTON_LEFT:
				self->openMouseOperate(window, true);
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				//printf("Mosue middle button clicked!");
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				//printf("Mosue right button clicked!");
				break;
			default:
				return;
			}
			return;

		});
	}

	void openMouseOperate(GLFWwindow* window, bool isOpen) {
		if (isOpen) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 捕获光标
			m_firstMouse = true;

			// 鼠标移动
			g_PrevUserCallbackPos = glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
				auto self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
				self->mouseEulerMove(xpos, ypos);
			});

			// 缩放操作
			g_PrevUserCallbackScroll =  glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
				auto self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
				self->mouseScroll(xoffset, yoffset);
			});
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, g_PrevUserCallbackPos);
			glfwSetScrollCallback(window, g_PrevUserCallbackScroll);
		}
		
	}

	void mouseScroll(double xoffset, double yoffset) {
		m_cameraFov -= yoffset;
		if (m_cameraFov <= 1.0f) {
			m_cameraFov = 1.0f;
		}
		if (m_cameraFov >= 45.0f) {
			m_cameraFov = 45.0f;
		}
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

		// 旋转90度之后 视角会发生逆转
		if (m_cameraPitch > 89.0f)
			m_cameraPitch = 89.0f;
		if (m_cameraPitch < -89.0f)
			m_cameraPitch = -89.0f;

		updateVector();
	}

	void updateVector() {
		glm::vec3 font;
		font.x = cos(glm::radians(m_cameraPitch)) * cos(glm::radians(m_cameraYaw));
		font.y = sin(glm::radians(m_cameraPitch));
		font.z = cos(glm::radians(m_cameraPitch)) * sin(glm::radians(m_cameraYaw));
		m_cameraFont = glm::normalize(font);
		m_cameraRight = glm::normalize(glm::cross(m_cameraFont, m_worldUp));

		// 可以使用CameraUp or WorldUp
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
	float m_cameraFov;
	glm::vec3 m_worldUp;

	GLFWscrollfun g_PrevUserCallbackScroll = NULL;
	GLFWcursorposfun g_PrevUserCallbackPos = NULL;
};