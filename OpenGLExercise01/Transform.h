#pragma once
class Transform
{
public:
	Transform(Shader* shader);

	void setProjection(float fov) {
		m_projectionMatrix = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
		m_shader->setMat("projection", glm::value_ptr(m_projectionMatrix));
	}

	void setPosition(glm::vec3 pos) {
		m_modelMatrix = glm::translate(glm::mat4(1.0f), pos);
		m_shader->setMat("model", glm::value_ptr(m_modelMatrix));
	}

	void setRotate(float angle, glm::vec3 axis) {
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(angle), axis);
		m_shader->setMat("model", glm::value_ptr(m_modelMatrix));
	}

	void setViewMartix(glm::mat4 martix) {
		m_viewMatrix = martix;
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