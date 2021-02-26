#pragma once
#include <vector>
#include "Shader.h"
#include "StructCollect.h"

class Mesh
{
public:
	/* �������� */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	
	// ��Ⱦ
	void Draw(Shader& shader);

private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;

	// ��ʼ������
	void setupMesh();
};