#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	glBindVertexArray(VAO);

	/* 绑定纹理贴图 */
	//texture_diffuse
	//texture_specular
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for  (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // 激活纹理单元

		std::string number;
		std::string name = textures[i].Type;

		if (name == "texture_diffuse") 
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		shader.setInt(("material." + name + number), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].Id); // 绑定纹理生成后的ID
	}
	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);

	/* 绘制网格 */
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // 根据EBO索引缓存进行绘制
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	/* 初始化 VAO、VBO、EBO */
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	/* 绑定顶点和索引缓存数据 */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*
		GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
		GL_DYNAMIC_DRAW: the data is likely to change a lot.
		GL_STREAM_DRAW: the data will change every time it is drawn.
	*/
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	/* 绑定特征值[0-15]; 对应顶点着色器中的位置 */

	// 位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// 法线坐标
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	// TODO: 是否需要重置
	glBindVertexArray(0);
}
