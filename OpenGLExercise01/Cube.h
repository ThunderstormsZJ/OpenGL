#pragma once
#include "Model.h"

#pragma region Vertices
const float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
};
//const float vertices[] = {
////  ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};

//unsigned int indies[] = {
//	2,1,0,
//	0,3,2
//};
#pragma endregion

// ����һ��������
class Cube:public Model
{
public:
	Cube(Shader* shader):Model(shader) {
		m_shader->use();
		// VAO��ʼ��
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// VBO��ʼ��
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		/*
			GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
			GL_DYNAMIC_DRAW: the data is likely to change a lot.
			GL_STREAM_DRAW: the data will change every time it is drawn.
		*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// EBO (Element Buffer Object) ��ʼ��
		// ��������
		/*unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indies), indies, GL_STATIC_DRAW);*/

		// �˴�������ֵ0��ΧΪ[0-15]
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//// ��ɫ
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3  * sizeof(float)));
		//glEnableVertexAttribArray(1);

		// UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void render() {
		Model::render();
		//  ��ѭ���а��� ���ڶ��������Ƶ����
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void update(float delataTime) {}

	void destroy() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		//glDeleteBuffers(1, &EBO);
	}

	void setTexture(std::string imgPath, std::string name, int index) {
		// ����ͼƬ
		stbi_set_flip_vertically_on_load(true);
		unsigned int texture = loadTexture(imgPath, index);
		m_shader->setInt(name, index);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

private:
	unsigned int VAO;
	unsigned int VBO;
	std::vector<unsigned int> textures;
};