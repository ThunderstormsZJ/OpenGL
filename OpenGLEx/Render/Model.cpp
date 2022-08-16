#include "Model.h"

Model::Model(std::string path, Shader& shader):Node(shader)
{
	loadModel(path);
}

void Model::Render()
{
	Node::Render();

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::Destroy()
{
}

void Model::Update(float delataTime)
{
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	/*
		������ (����ѡ��˵��)��
			aiProcess_Triangulate: ��ͼԪ��״ȫ��ת��Ϊ������
			aiProcess_FlipUVs: ������תy�����������
			aiProcess_GenNormals: �����������������Ϊÿ��ģ�ʹ���������
			aiProcess_SplitLargeMeshes: ���ϴ������ָ�ɸ�С������
			aiProcess_OptimizeMeshes: ��һЩС����ƴ�ӳɴ����񣬼��ٻ��Ƶĵ���
	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		// ���ģ���Ƿ���سɹ�
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of("/"));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// ����Mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// �����ӽڵ�
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	/* �����������ꡢ���������������� */
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		// Assimp ����һ��ģ����һ������������8����ͬ����������
		// �����ǲ����õ���ô�࣬ ֻ���ĵ�һ�����������
		if (mesh->mTextureCoords[0]) {
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else {
			vertex.TexCoords = glm::vec2(0, 0);
		}
		vertices.push_back(vertex);
	}

	/* �������� */
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	/* �������� */
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		// diffuse
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// specular
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// normal
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// height
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	/* ���������еĲ��� */
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		// ��ȡ����·��
		// ���ﴦ���������·��
		// ���ϵ�ĳЩģ�Ϳ����Ǿ���·��������Ҫ���⴦��
		aiString path;
		mat->GetTexture(type, i, &path);
		bool skip = false;
		for (unsigned int i = 0; i < textures_loaded.size(); i++)
		{
			if (std::strcmp(textures_loaded[i].Path.data(), path.C_Str()) == 0) {// ��������
				textures.push_back(textures_loaded[i]);
				skip = true;
				break;
			}
		}

		if (!skip) { // ����һ������
			Texture texture;
			texture.Type = typeName;
			texture.Id = ImgCache::GetInstance().addTexture(directory + "/" + path.C_Str());
			texture.Path = path.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
}