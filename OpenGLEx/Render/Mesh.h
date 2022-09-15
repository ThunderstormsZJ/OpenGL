#pragma once
#include <vector>
#include "Shader.h"
#include "../Common/StructCollect.h"

class Mesh
{
public:
	/* 网格数据 */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

	~Mesh();

	// 渲染
	void Draw(Shader& shader);
	void AddTexture(Texture texture);

	void Dispose();

private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;

	// 初始化缓冲
	void setupMesh();
};