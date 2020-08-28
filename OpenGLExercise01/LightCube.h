#pragma once
#include "Cube.h"

class LightCube: public Cube
{
public:
	LightCube(Lamp* lamp):Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl")) 
	, m_lamp(lamp){

	}

	void render() {
		Cube::render();

		updateLightRender();
	}

private:
	Lamp* m_lamp;

	void updateLightRender() {
		m_shader->setVec3("viewPos", glm::value_ptr(m_camera->getPos()));
		m_shader->setVec3("objectColor", glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
		m_shader->setVec3("lightColor", glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		m_shader->setVec3("lightPos", glm::value_ptr(m_lamp->Position));
	}
};