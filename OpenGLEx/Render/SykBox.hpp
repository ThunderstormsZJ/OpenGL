#include "Node.h"

#ifndef h_SkyBox

const float skyboxVertices[] = {
	// positions        
	// 后面
	-1.0f,  1.0f, -1.0f, //左上
	-1.0f, -1.0f, -1.0f, //左下 
	 1.0f, -1.0f, -1.0f, //右下
	 1.0f, -1.0f, -1.0f, //右下 
	 1.0f,  1.0f, -1.0f, //右上 
	-1.0f,  1.0f, -1.0f, //左上 
	// 左面
	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	 // 右面
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 // 前面
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	 // 上面
	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	 // 下面
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

class SkyBox : public Node {
public:
	SkyBox(Shader& shader, GLuint cubeMapId): Node(shader) {
		this->CubeMapId = cubeMapId;
		// VAO初始化
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// VBO初始化
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	~SkyBox() {
		Destroy();
	}
	
	void Update(float delataTime) override {}

	void Destroy() override {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Render() override {
		glDepthFunc(GL_LEQUAL);

		Node::Render();

		shader.setInt("skybox", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->CubeMapId);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
	}
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int CubeMapId;
};

#endif // !h_SkyBox
