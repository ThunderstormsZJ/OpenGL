#pragma once
#include "Cube.h"
#include "Utils.h"

class LightCube: public Cube
{
public:
	LightCube(WindowContext* content, Material* material):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl"))
	, m_content(content), m_material(material){
		setTexture(&m_material->Diffuse);
		setTexture(&m_material->Specular);
		setTexture(&m_material->Emission);
	}

	~LightCube() {
	}

	void updateShader() {
		Cube::updateShader();
		updateLightRender();
	}

private:
	WindowContext* m_content;
	Material* m_material;

	void updateLightRender() {
		m_shader->setInt("material.shininess", m_material->Shininess);

		// 平行光
		DirLight* dirLight = &m_content->tool->dirLight;
		m_shader->setBool("dirLight.isOpen", dirLight->IsOpen);
		m_shader->setVec3("dirLight.direction", glm::value_ptr(*dirLight->Direction));
		m_shader->setVec3("dirLight.ambient", glm::value_ptr(glm::vec3(dirLight->Ambient * dirLight->Color))); // 将光照调暗了一些以搭配场景
		m_shader->setVec3("dirLight.diffuse", glm::value_ptr(glm::vec3(dirLight->Diffuse * dirLight->Color)));
		m_shader->setVec3("dirLight.specular", glm::value_ptr(glm::vec3(dirLight->Specular * dirLight->Color)));

		// 点光源
		for (int i = 0; i < m_content->tool->pointLightCount; i++)
		{
			PointLight* pointLight = m_content->tool->pointLights[i];
			std::string name = format("pointLights[%d].", i);
			m_shader->setBool(name + "position", pointLight->Position);
			m_shader->setBool(name + "isOpen", pointLight->IsOpen);
			m_shader->setVec3(name + "ambient", glm::value_ptr(glm::vec3(pointLight->Ambient * pointLight->Color)));
			m_shader->setVec3(name + "diffuse", glm::value_ptr(glm::vec3(pointLight->Diffuse * pointLight->Color)));
			m_shader->setVec3(name + "specular", glm::value_ptr(glm::vec3(pointLight->Specular * pointLight->Color)));

			m_shader->setFloat(name + "constant", pointLight->Constant);
			m_shader->setFloat(name + "linear", pointLight->Linear);
			m_shader->setFloat(name + "quadratic", pointLight->Quadratic);
		}
	}
};