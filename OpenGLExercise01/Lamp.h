#pragma once
#include "Cube.h"

class Lamp: public Cube
{
public:
	Lamp(): Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_lamp_FragmentShader.glsl")) {
		setPosition(glm::vec3(1.2f, 1.0, 2.0f));
		setScale(0.2);
	}
private:

};