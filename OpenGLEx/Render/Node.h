#pragma once
#include "Director.h"
#include "Shader.h"
#include "../Utils/Logger.hpp"
#include <rotate_vector.hpp>

class Node
{
public:
	Node(Shader &shader)
		:shader(shader),
		material(nullptr)
	{
		renderShader = &this->shader;
		renderShader->use();
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
		this->transMat = glm::translate(glm::mat4(1.0f), position);
	}

	void SetScale(float scale) {
		this->scale = glm::vec3(scale);
		this->scaleMat = glm::scale(glm::mat4(1.0f), this->scale);
	}

	void SetScale(float x, float y, float z) {
		this->scale = glm::vec3(x, y, z);
		this->scaleMat = glm::scale(glm::mat4(1.0f), this->scale);
	}

	void SetRotate(float x = 0, float y = 0, float z = 0) {
		this->rotateAngle = glm::vec3(x, y, z);
		this->rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1, 0, 0));
		this->rotateMat = glm::rotate(this->rotateMat, glm::radians(y), glm::vec3(0, 1, 0));
		this->rotateMat = glm::rotate(this->rotateMat, glm::radians(z), glm::vec3(0, 0, 1));
	}

	void SetColor(glm::vec3 color) {
		this->color = color;
	}

	void Rotate(float x = 0, float y = 0, float z = 0) {
		this->rotateAngle += glm::vec3(x, y, z);

		// 全局坐标轴转换
		glm::vec3 xNorm(1.0, 0.0f, 0.0);
		glm::vec3 yNorm(0.0, 1.0f, 0.0);
		glm::vec3 zNorm(0.0, 0.0f, 1.0);
		this->rotateMat = glm::rotate(this->rotateMat, glm::radians(x), xNorm); // Rotate on X axis
		yNorm = glm::rotate(yNorm, glm::radians(-this->rotateAngle.x), xNorm);
		this->rotateMat = glm::rotate(this->rotateMat, glm::radians(y), yNorm); // Rotate on Y axis
		zNorm = glm::rotate(zNorm, glm::radians(-this->rotateAngle.y), yNorm);
		this->rotateMat = glm::rotate(this->rotateMat, glm::radians(z), zNorm); // Rotate on Z axis
	}

	void SetName(std::string v) { name = v; }
	std::string GetName() { return name; }
	void SetTag(std::string v) { tag = v; }
	std::string GetTag() { return tag; }

	virtual void Render() {
		renderShader->use();
		updateMatrixRender();
		updateLightRender();
	};
	virtual void Destroy() = 0;
	virtual void Update(float delataTime) = 0;

protected:
	Shader shader;
	Shader* renderShader;

private:
	/* Self Property */
	glm::vec3 position = glm::vec3(0);
	glm::vec3 color = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	glm::vec3 rotateAngle = glm::vec3(0);

	Material* material;

	glm::mat4 transMat = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::mat4(1.0f);
	glm::mat4 rotateMat = glm::mat4(1.0f);

	/* Other Property */
	std::string name;
	std::string tag;

	void updateMatrixRender() {
		// 缩放 -> 旋转 -> 位移
		// 代码中得顺序相反
		glm::mat4 modelMatrix = transMat * rotateMat * scaleMat;

		Camera* camera = Director::GetInstance().MainCamera;
		glm::mat4 projection = glm::perspective(glm::radians(camera->getFov()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera->getViewMartix();

		renderShader->setMat("model", glm::value_ptr(modelMatrix)); // 模型矩阵
		renderShader->setMat("projection", glm::value_ptr(projection)); // 透视矩阵
		renderShader->setMat("view", glm::value_ptr(view)); // 观察矩阵

		renderShader->setVec3("objectColor", glm::value_ptr(color)); // 颜色
	}

	void updateLightRender() {

		// 设置材质Shininess
		if (material != nullptr) 
			renderShader->setInt("material.shininess", material->Shininess);
		else 
			renderShader->setInt("material.shininess", 2);

		// 平行光
		DirLight* dirLight = Director::GetInstance().GetPDirLight();
		renderShader->setBool("dirLight.isOpen", dirLight->IsOpen);
		if (dirLight->IsOpen) {
			renderShader->setVec3("dirLight.direction", glm::value_ptr(dirLight->Direction));
			renderShader->setVec3("dirLight.ambient", glm::value_ptr(glm::vec3(dirLight->Ambient * dirLight->Color))); // 将光照调暗了一些以搭配场景
			renderShader->setVec3("dirLight.diffuse", glm::value_ptr(glm::vec3(dirLight->Diffuse * dirLight->Color)));
			renderShader->setVec3("dirLight.specular", glm::value_ptr(glm::vec3(dirLight->Specular * dirLight->Color)));
		}

		// 点光源
		std::vector<PointLight>* pointLights = Director::GetInstance().GetPPointLights();
		for (int i = 0; i < pointLights->size(); i++)
		{
			PointLight* pointLight = &pointLights->at(i);
			std::string name = format("pointLights[%d].", i);
			renderShader->setBool(name + "isOpen", pointLight->IsOpen);
			if (pointLight->IsOpen) {
				renderShader->setVec3(name + "position", glm::value_ptr(pointLight->Position));
				renderShader->setVec3(name + "ambient", glm::value_ptr(glm::vec3(pointLight->Ambient * pointLight->Color)));
				renderShader->setVec3(name + "diffuse", glm::value_ptr(glm::vec3(pointLight->Diffuse * pointLight->Color)));
				renderShader->setVec3(name + "specular", glm::value_ptr(glm::vec3(pointLight->Specular * pointLight->Color)));

				renderShader->setFloat(name + "constant", pointLight->Constant);
				renderShader->setFloat(name + "linear", pointLight->Linear);
				renderShader->setFloat(name + "quadratic", pointLight->Quadratic);
			}
		}

		// 聚光灯
		SpotLight* spotLight = Director::GetInstance().GetPSpotLight();
		renderShader->setBool("spotLight.isOpen", spotLight->IsOpen);
		if (spotLight->IsOpen) {
			renderShader->setVec3("spotLight.position", glm::value_ptr(spotLight->Position));
			renderShader->setVec3("spotLight.direction", glm::value_ptr(spotLight->Direction));
			renderShader->setFloat("spotLight.cutOff", glm::cos(spotLight->CutOffRad));
			renderShader->setFloat("spotLight.outerCutOff", glm::cos(spotLight->CutOffRad + glm::radians(spotLight->SmoothEdgeIntensity)));
			renderShader->setVec3("spotLight.ambient", glm::value_ptr(glm::vec3(spotLight->Ambient) * spotLight->Color));
			renderShader->setVec3("spotLight.diffuse", glm::value_ptr(glm::vec3(spotLight->Diffuse) * spotLight->Color));
			renderShader->setVec3("spotLight.specular", glm::value_ptr(glm::vec3(spotLight->Specular) * spotLight->Color));

			renderShader->setFloat("spotLight.constant", spotLight->Constant);
			renderShader->setFloat("spotLight.linear", spotLight->Linear);
			renderShader->setFloat("spotLight.quadratic", spotLight->Quadratic);
		}
	}
};