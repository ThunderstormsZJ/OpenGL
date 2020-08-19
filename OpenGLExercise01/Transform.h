#pragma once
class Transform
{
public:
	Transform(Shader* shader);

	void setProjection(float fov) {
		m_projectionMatrix = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
	}

	void setPosition(glm::vec3 pos) {
		m_modelMatrix = glm::translate(glm::mat4(1.0f), pos);
	}

	void setScale(float scale) {
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(scale, scale, scale));
	}

	void setScale(float x, float y, float z) {
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(x, y, z));
	}

	void setRotate(float angle, glm::vec3 axis) {
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), axis);
	}

	void setViewMartix(glm::mat4 martix) {
		m_viewMatrix = martix;
	}

	void updateMartix() {
		m_shader->setMat("projection", glm::value_ptr(m_projectionMatrix));
		m_shader->setMat("model", glm::value_ptr(m_modelMatrix));
		m_shader->setMat("view", glm::value_ptr(m_viewMatrix));
	}

private:
	Shader* m_shader;

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);	// Model Matrix
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);    // View Matrix
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);  // Projection Matrix
};

Transform::Transform(Shader* shader) : m_shader(shader) {

}