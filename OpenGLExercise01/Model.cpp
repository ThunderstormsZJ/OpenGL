#include "Model.h"

Model::Model(std::string path, Shader &shader, Camera* camera)
	:shader(shader)
{
	shader.use();
	this->camera = camera;
	loadModel(path);
}

void Model::Render()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	glm::mat4 projection = glm::perspective(glm::radians(camera->getFov()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->getViewMartix();

	shader.setMat("model", glm::value_ptr(model)); // 模型矩阵
	shader.setMat("projection", glm::value_ptr(projection)); // 透视矩阵
	shader.setMat("view", glm::value_ptr(view)); // 观察矩阵

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	/*
		参数二 (常用选项说明)：
			aiProcess_Triangulate: 将图元形状全部转换为三角形
			aiProcess_FlipUVs: 处理翻转y轴的纹理坐标
			aiProcess_GenNormals: 如果不包含法向量，为每个模型创建法向量
			aiProcess_SplitLargeMeshes: 将较大的网格分割成更小的网格
			aiProcess_OptimizeMeshes: 将一些小网格拼接成大网格，减少绘制的调用
	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		// 检测模型是否加载成功
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
		// 处理Mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// 处理子节点
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

	/* 解析顶点坐标、法向量、纹理坐标 */
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		// Assimp 允许一个模型在一个顶点包含最多8个不同的纹理坐标
		// 而我们不会用到这么多， 只关心第一组的纹理坐标
		if (mesh->mTextureCoords[0]) {
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else {
			vertex.TexCoords = glm::vec2(0, 0);
		}
		vertices.push_back(vertex);
	}

	/* 解析索引 */
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	/* 解析材质 */
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
	/* 加载纹理中的材质 */
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		// 获取纹理路径
		// 这里处理的是相对路径
		// 网上的某些模型可能是绝对路径，这需要额外处理
		aiString path;
		mat->GetTexture(type, i, &path);
		
		Texture texture;
		texture.Type = typeName;
		texture.Id = ImgCache::GetInstance().addTexture(directory + "/" + path.C_Str());

		textures.push_back(texture);
	}

	return textures;
}
