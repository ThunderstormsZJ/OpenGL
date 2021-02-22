#pragma once
#include "Cube.h"

class Lamp: public Cube
{
public:
	Lamp(): Cube(new Shader("Shader/light_VertextShader.glsl", "Shader/light_lamp_FragmentShader.glsl")) {
		setScale(0.2);
	}
private:

};