#pragma once
#include "Node.h"
#include "../Common/StructCollect.h"
#include "../Utils/ImgCache.hpp"

#pragma region Vertices
const float boxVertices[] = {
	// positions
						  // texture Coords
									  // Normal
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

const float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f, 0.0f, -1.0f,  0.0f,

	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f, 0.0f, -1.0f,  0.0f,
	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f, 0.0f, -1.0f,  0.0f,
};

float transparentVertices[] = {
	// positions         // texture Coords
	0.0f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f, // 左上
	0.0f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f, // 左下
	1.0f, -0.5f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, // 右下
		  
	0.0f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f, // 左上
	1.0f, -0.5f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, // 右下
	1.0f,  0.5f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f, // 右上
};
//const float vertices[] = {
////  ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

//unsigned int indies[] = {
//	2,1,0,
//	0,3,2
//};
#pragma endregion

// 生成一个正方体
class Cube:public Node
{
public:
	Cube(Shader& shader, CubeType cType = CubeType::Box, bool openOutLine = false):Node(shader) {
		m_cType = cType;
		m_openOutLine = openOutLine;

		// VAO初始化
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// VBO初始化
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		if (cType == CubeType::Box) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
			vertCount = 36;
		}
		else if (cType == CubeType::Panel) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
			vertCount = 6;
		}
		else if (cType == CubeType::Transparent){
			glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
			vertCount = 6;
		}

		// 此处的特征值0范围为[0-15]
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//// 颜色
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3  * sizeof(float)));
		//glEnableVertexAttribArray(1);

		// UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Normal
		if (cType == CubeType::Box) {		
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
			glEnableVertexAttribArray(3);
		}

		//glDrawArrays(GL_TRIANGLES, 0, vertCount);

		if (m_openOutLine) {
			m_outLineShader = new Shader("Shader/Texture_VertextShader.glsl", "Shader/TextureOutLine_FragmentShader.glsl");
		}
	}

	~Cube() {
		Destroy();
	}

	void Update(float delataTime) override{}
	void Destroy() override {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	void Render() override {
		// 画线框
		if (m_openOutLine) {
			glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
			glStencilMask(0xFF); // 启用模板缓冲写入
		}
		else {
			glStencilMask(0x00); // 禁用模板缓冲写入
		}

		Node::Render();

		glBindTexture(GL_TEXTURE_2D, 0);
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			shader.setInt(textures[i].Name, i);
			glActiveTexture(GL_TEXTURE0 + i); // 激活纹理单元
			glBindTexture(GL_TEXTURE_2D, textures[i].Id);
			//glActiveTexture(GL_TEXTURE0);
		}

		//  在循环中绑定是 用于多个物体绘制的情况
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		glBindVertexArray(0);

		// 线框
		if (m_openOutLine) {
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // 绘制不等于1的部分
			glStencilMask(0x00); // 禁止写入
			//glDisable(GL_DEPTH_TEST); // 禁止深度测试
			// 绘制线框
			this->SetScale(1.05);
			this->renderShader = this->m_outLineShader;
			
			Node::Render();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, vertCount);
			glBindVertexArray(0);

			// 还原
			this->renderShader = &this->shader;
			this->SetScale(1);
			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}

	}

	void SetTexture(std::string imgPath, std::string name, GLint param = GL_REPEAT) {
		stbi_set_flip_vertically_on_load(true);
		Texture texture;
		texture.Id = ImgCache::GetInstance().addTexture(imgPath, param);	// 加载图片
		texture.Name = name;
		texture.Path = imgPath;

		textures.push_back(texture);
	}

private:
	unsigned int vertCount = 0;// 顶点个数
	unsigned int VAO;
	unsigned int VBO;
	std::vector<Texture> textures;
	CubeType m_cType; // 物体类型
	bool m_openOutLine; // 是否开启边框
	Shader* m_outLineShader; // 边框shader
};