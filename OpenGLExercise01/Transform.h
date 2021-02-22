#pragma once

// 模型的基本属性
class Transform
{
public:
	Transform() {}
	Transform(Shader* shader):m_shader(shader) {}
	virtual ~Transform() { printf("[Log]Delete Transform\n"); }

	Shader* getShader() { return m_shader; }
	glm::vec3 getPos() { return *m_position; }
	glm::vec3* getPPos() { return m_position; }
	glm::vec3* getPPColor() { return m_color; }
 
	void setProjection(float fov) {
		m_projectionMatrix = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
	}

	void setPosition(glm::vec3* pos) {
		m_position = pos;
	}

	void setScale(float scale) {
		m_scale = new glm::vec3(scale);
	}

	void setScale(float x, float y, float z) {
		m_scale = new glm::vec3(x, y, z);
	}

	void setRotate(float angle, glm::vec3 axis) {
		m_rotateAngle = angle;
		m_rotateAxis = axis;
	}

	void setViewMartix(glm::mat4 martix) {
		m_viewMatrix = martix;
	}

	void setColor(glm::vec3* color) {
		m_color = color;
	}

	void updateModelMatrix() {
		// 缩放 -> 旋转 -> 位移
		// 代码中得顺序相反
		m_modelMatrix = glm::translate(glm::mat4(1.0f), *m_position);
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotateAngle), m_rotateAxis);
		m_modelMatrix = glm::scale(m_modelMatrix, *m_scale);
	}

	virtual void updateShader() {
		updateModelMatrix();

		m_shader->setMat("model", glm::value_ptr(m_modelMatrix)); // 模型矩阵
		m_shader->setMat("projection", glm::value_ptr(m_projectionMatrix)); // 透视矩阵
		m_shader->setMat("view", glm::value_ptr(m_viewMatrix)); // 观察矩阵
		
		m_shader->setVec3("objectColor", glm::value_ptr(*m_color)); // 颜色
	}

protected:
	glm::vec3* m_position = new glm::vec3(0);
	glm::vec3* m_color = new glm::vec3(0);
	glm::vec3* m_scale = new glm::vec3(1);
	glm::vec3 m_rotateAxis = glm::vec3(1);
	float m_rotateAngle = 0;

	Shader* m_shader = nullptr;

private:
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);	// Model Matrix
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);    // View Matrix
	glm::mat4 m_projectionMatrix = glm::mat4(1.0f);  // Projection Matrix
};