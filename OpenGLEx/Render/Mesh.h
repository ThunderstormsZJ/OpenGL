#pragma once
#include <vector>
#include "Shader.h"
#include "../Common/StructCollect.h"

class Mesh
{
public:
	/* �������� */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

	~Mesh();

	// ��Ⱦ
	void Draw(Shader& shader);
	void AddTexture(Texture texture);

	void Dispose();

private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;

	// ��ʼ������
	void setupMesh();
};