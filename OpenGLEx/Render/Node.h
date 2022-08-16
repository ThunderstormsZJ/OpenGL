#pragma once
#include "Director.h"
#include "Shader.h"
#include "../Utils/Logger.hpp"

class Node
{
public:
	Node(Shader &shader)
		:shader(shader),
		material(nullptr)
	{
		shader.use();
		name = typeid(this).name();
	}

	~Node() {
		Logger.Instance->info("Node[{}] Delete", this->name);
	}

	glm::vec3 GetPos() { return position; }
	glm::vec3* GetPPos() { return &position; }
	glm::vec3* GetPPColor() { return &color; }
	Shader* GetShader() { return &shader; }

	void SetMaterial(Material* material) {
		this->material = material;
	}

	void SetPosition(glm::vec3 pos) {
		this->position = pos;
	}

	void SetScale(float scale) {
		this->scale = glm::vec3(scale);
	}

	void SetScale(float x, float y, float z) {
		this->scale = glm::vec3(x, y, z);
	}

	void SetRotate(float angle, glm::vec3 axis) {
		this->rotateAngle = angle;
		this->rotateAxis = axis;
	}

	void SetColor(glm::vec3 color) {
		this->color = color;
	}

	void SetName(std::string v) { name = v; }
	std::string GetName() { return name; }
	void SetTag(std::string v) { tag = v; }
	std::string GetTag() { return tag; }

	virtual void Render() {
		shader.use();
		updateMatrixRender();
		updateLightRender();
	};
	virtual void Destroy() = 0;
	virtual void Update(float delataTime) = 0;

protected:
	Shader shader;

private:
	/* Self Property */
	glm::vec3 position = glm::vec3(0);
	glm::vec3 color = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	glm::vec3 rotateAxis = glm::vec3(1);
	float rotateAngle = 0;

	Material* material;

	glm::mat4 modelMatrix = glm::mat4(1.0f);	// Model Matrix

	/* Other Property */
	std::string name;
	std::string tag;

	void updateMatrixRender() {
		// 缩放 -> 旋转 -> 位移
		// 代码中得顺序相反
		modelMatrix = glm::translate(glm::mat4(1.0f), position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotateAngle), rotateAxis);
		modelMatrix = glm::scale(modelMatrix, scale);

		Camera* camera = Director::GetInstance().MainCamera;
		glm::mat4 projection = glm::perspective(glm::radians(camera->getFov()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera->getViewMartix();

		shader.setMat("model", glm::value_ptr(modelMatrix)); // 模型矩阵
		shader.setMat("projection", glm::value_ptr(projection)); // 透视矩阵
		shader.setMat("view", glm::value_ptr(view)); // 观察矩阵

		shader.setVec3("objectColor", glm::value_ptr(color)); // 颜色
	}

	void updateLightRender() {

		// 设置材质Shininess
		if (material != nullptr) 
			shader.setInt("material.shininess", material->Shininess);
		else 
			shader.setInt("material.shininess", 2);

		// 平行光
		DirLight* dirLight = Director::GetInstance().GetPDirLight();
		shader.setBool("dirLight.isOpen", dirLight->IsOpen);
		if (dirLight->IsOpen) {
			shader.setVec3("dirLight.direction", glm::value_ptr(dirLight->Direction));
			shader.setVec3("dirLight.ambient", glm::value_ptr(glm::vec3(dirLight->Ambient * dirLight->Color))); // 将光照调暗了一些以搭配场景
			shader.setVec3("dirLight.diffuse", glm::value_ptr(glm::vec3(dirLight->Diffuse * dirLight->Color)));
			shader.setVec3("dirLight.specular", glm::value_ptr(glm::vec3(dirLight->Specular * dirLight->Color)));
		}

		// 点光源
		std::vector<PointLight>* pointLights = Director::GetInstance().GetPPointLights();
		for (int i = 0; i < pointLights->size(); i++)
		{
			PointLight* pointLight = &pointLights->at(i);
			std::string name = format("pointLights[%d].", i);
			shader.setBool(name + "isOpen", pointLight->IsOpen);
			if (pointLight->IsOpen) {
				shader.setVec3(name + "position", glm::value_ptr(pointLight->Position));
				shader.setVec3(name + "ambient", glm::value_ptr(glm::vec3(pointLight->Ambient * pointLight->Color)));
				shader.setVec3(name + "diffuse", glm::value_ptr(glm::vec3(pointLight->Diffuse * pointLight->Color)));
				shader.setVec3(name + "specular", glm::value_ptr(glm::vec3(pointLight->Specular * pointLight->Color)));

				shader.setFloat(name + "constant", pointLight->Constant);
				shader.setFloat(name + "linear", pointLight->Linear);
				shader.setFloat(name + "quadratic", pointLight->Quadratic);
			}
		}

		// 聚光灯
		SpotLight* spotLight = Director::GetInstance().GetPSpotLight();
		shader.setBool("spotLight.isOpen", spotLight->IsOpen);
		if (spotLight->IsOpen) {
			shader.setVec3("spotLight.position", glm::value_ptr(spotLight->Position));
			shader.setVec3("spotLight.direction", glm::value_ptr(spotLight->Direction));
			shader.setFloat("spotLight.cutOff", glm::cos(spotLight->CutOffRad));
			shader.setFloat("spotLight.outerCutOff", glm::cos(spotLight->CutOffRad + glm::radians(spotLight->SmoothEdgeIntensity)));
			shader.setVec3("spotLight.ambient", glm::value_ptr(glm::vec3(spotLight->Ambient) * spotLight->Color));
			shader.setVec3("spotLight.diffuse", glm::value_ptr(glm::vec3(spotLight->Diffuse) * spotLight->Color));
			shader.setVec3("spotLight.specular", glm::value_ptr(glm::vec3(spotLight->Specular) * spotLight->Color));

			shader.setFloat("spotLight.constant", spotLight->Constant);
			shader.setFloat("spotLight.linear", spotLight->Linear);
			shader.setFloat("spotLight.quadratic", spotLight->Quadratic);
		}
	}
};