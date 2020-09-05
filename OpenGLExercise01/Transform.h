#pragma once

// 模型的基本属性
class Transform
{
public:
	Transform() {}
	Transform(Shader* shader):m_shader(shader) {}

	Shader* getShader() { return m_shader; }
	glm::vec3 getPos() { return m_position; }
	glm::vec3* getPPos() { return &m_position; }
	glm::vec3* getPPColor() { return m_color; }
 
	void setProjection(float fov) {
		m_projectionMatrix = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
	}

	void setPosition(glm::vec3 pos) {
		m_position = pos;
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

	void setColor(glm::vec3* color) {
		m_color = color;
	}

	virtual void updateShader() {
		m_shader->setMat("projection", glm::value_ptr(m_projectionMatrix)); // 透视矩阵
		m_shader->setMat("model", glm::value_ptr(m_modelMatrix)); // 模型矩阵
		m_shader->setMat("view", glm::value_ptr(m_viewMatrix)); // 观察矩阵
		
		m_shader->setVec3("objectColor", glm::value_ptr(*m_color)); // 颜色
	}

protected:
	glm::vec3* m_color = new glm::vec3(0);
	glm::vec3 m_position = glm::vec3(0, 0, 0);
	Shader* m_shader = nullptr;

private:
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);	// Model Matrix
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);    // View Matrix
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);  // Projection Matrix
};