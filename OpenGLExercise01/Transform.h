#pragma once
class Transform
{
public:
	Transform(Shader* shader);

	void updateTransform() {
		m_modelMatrix = glm::rotate(m_modelMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
		m_projectionMatrix = glm::perspective(glm::radians(45.0f), 1280.0f/720.0f, 0.1f, 100.0f);

		glm::mat4 transformMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
		m_shader->setMat("transform", glm::value_ptr(transformMatrix));
	}

	void setPosition(glm::vec3 pos) {
		m_modelMatrix = glm::translate(glm::mat4(1.0f), pos);
	}

	void setViewMartix(glm::mat4 martix) {
		m_viewMatrix = martix;
	}

private:
	Shader* m_shader;

	glm::mat4 m_modelMatrix = glm::mat4(1.0f);	// Model Matrix
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);    // View Matrix
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);  // Projection Matrix
};

Transform::Transform(Shader* shader) : m_shader(shader) {

}