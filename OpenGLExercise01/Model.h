#pragma once
#include "Shader.h"
#include "stb_image.h"
#include "Transform.h"
#include "ImgCache.h"

// 处理模型的Shader属性
class Model : public Transform
{
public:
	using Transform::Transform;

	virtual void update(float delataTime) = 0;
	virtual void render() {
		m_shader->use();
		setViewMartix(m_camera->getViewMartix());
		setProjection(m_camera->getFov());
		updateShader();
	}

	virtual void destroy() = 0;
	void setName(std::string v) { m_name = v; }
	std::string getName() { return m_name; }
	void setTag(std::string v) { m_tag = v; }
	std::string getTag() { return m_tag; }
	void setCamera(Camera* camera) { m_camera = camera; }
	Camera* getCamera() { return m_camera; }

protected:
	std::string m_name;
	std::string m_tag;
	Camera* m_camera;

	// 设置纹理
	unsigned int loadTexture(std::string imgPath, int textureIndex) {
		if (imgPath.empty()) {
			return NULL;
		}

		// Texture 初始化
		unsigned int texture = ImgCache::GetInstance().addTexture(imgPath);

		return texture;
	}
private:

};