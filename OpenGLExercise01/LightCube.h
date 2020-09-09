#pragma once
#include "Cube.h"

class LightCube: public Cube
{
public:
	LightCube(Light* light):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl")) 
	, m_light(light){
		setTexture("Resources/container2.png", "material.diffuse", 0);
		setTexture("Resources/container2_specular.png", "material.specular", 1);
		//setTexture("Resources/matrix.jpg", "material.emission", 2);
		setTexture("", "material.emission", 2);
	}

	~LightCube() {
	}

	void updateShader() {
		Cube::updateShader();
		updateLightRender();
	}

private:
	Light* m_light;

	void updateLightRender() {
		m_shader->setVec3("lightPos", glm::value_ptr(*m_light->Position));

		m_shader->setFloat("material.shininess", 32.0f);

		m_shader->setVec3("light.ambient", glm::value_ptr(glm::vec3(m_light->Ambient)));
		m_shader->setVec3("light.diffuse", glm::value_ptr(m_light->Diffuse * m_light->Color)); // 将光照调暗了一些以搭配场景
		m_shader->setVec3("light.specular", glm::value_ptr(m_light->Specular * m_light->Color));
	}
};