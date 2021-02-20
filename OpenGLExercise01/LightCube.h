#pragma once
#include "Cube.h"

class LightCube: public Cube
{
public:
	LightCube(Light* light, Material* material):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl"))
	, m_light(light), m_material(material){
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
	Light* m_light;
	Material* m_material;

	void updateLightRender() {
		m_shader->setVec3("lightPos", glm::value_ptr(*m_light->Position));

		m_shader->setInt("material.shininess", m_material->Shininess);

		m_shader->setVec3("light.ambient", glm::value_ptr(glm::vec3(m_light->Ambient)));
		m_shader->setVec3("light.diffuse", glm::value_ptr(m_light->Diffuse * m_light->Color)); // 将光照调暗了一些以搭配场景
		m_shader->setVec3("light.specular", glm::value_ptr(m_light->Specular * m_light->Color));
	}
};