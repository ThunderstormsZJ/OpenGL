#pragma once
#include "Cube.h"

class LightCube :public Cube {
public:
	LightCube(Shader& shader) :Cube(shader) {

	}

	~LightCube() {

	}

	void SetLight(PointLight* light) {
		this->mLight = light;
	}

	PointLight* GetLight() {
		return this->mLight;
	}

	void Render() override {
		this->SetPosition(this->mLight->Position);
		this->SetColor(this->mLight->Color);

		Cube::Render();
	}
private:
	PointLight* mLight;
};