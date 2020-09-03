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

class LightCube: public Cube
{
public:
	LightCube(Lamp* lamp, Light* light):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl")) 
	, m_lamp(lamp)
	, m_light(light){
		
	}

	~LightCube() {
		delete m_light;
	}

	void render() {
		Cube::render();
		updateLightRender();
	}

private:
	Lamp* m_lamp;
	Light* m_light;

	void updateLightRender() {
		m_shader->setVec3("lightColor", glm::value_ptr(*m_light->Color));
		m_shader->setVec3("lightPos", glm::value_ptr(*m_light->Position));
	}
};