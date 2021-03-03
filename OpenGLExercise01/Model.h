#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "Node.h"
#include "ImgCache.h"
#include "Director.h"

class Model: public Node
{
public:
	Model(std::string path, Shader& shader);
	void Render() override;
	void Destroy() override;
	void Update(float delataTime) override;

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};