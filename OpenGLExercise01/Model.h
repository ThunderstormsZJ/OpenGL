#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "ImgCache.h"

class Model
{
public:
	Model(std::string path, Shader &shader, Camera* camera);
	void Render();

private:
	std::vector<Mesh> meshes;
	std::string directory;
	Shader shader;
	Camera* camera;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};