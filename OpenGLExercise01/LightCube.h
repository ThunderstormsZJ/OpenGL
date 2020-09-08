#pragma once
#include "Cube.h"

struct Light
{
	glm::vec3* ViewPos;
	glm::vec3* Color;
	glm::vec3* Position;

	~Light() {
		delete this->Color;
	}
};

struct Material 
{
	glm::vec3* ambient;
	glm::vec3* diffuse;
	glm::vec3* specular;
	float* shininess;
};

class LightCube: public Cube
{
public:
	LightCube(Lamp* lamp, Light* light):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl")) 
	, m_lamp(lamp)
	, m_light(light){
		setTexture("Resources/container2.png", "material.diffuse", 0);
		setTexture("Resources/container2_specular.png", "material.specular", 1);
		setTexture("Resources/matrix.jpg", "material.emission", 2);
	}

	~LightCube() {
		delete m_light;
	}

	void updateShader() {
		Cube::updateShader();
		updateLightRender();
	}

private:
	Lamp* m_lamp;
	Light* m_light;

	void updateLightRender() {
		m_shader->setVec3("lightColor", glm::value_ptr(*m_light->Color));
		m_shader->setVec3("lightPos", glm::value_ptr(*m_light->Position));

		//m_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		//m_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		//m_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		m_shader->setFloat("material.shininess", 32.0f);

		m_shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		m_shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
		m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	}
};