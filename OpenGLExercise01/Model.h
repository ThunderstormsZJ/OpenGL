#pragma once
#include "Shader.h"
#include "stb_image.h"
#include "Transform.h"

class Model : public Transform
{
public:
	using Transform::Transform;

	virtual void update(float delataTime) = 0;
	virtual void render() {
		m_shader->use();
		setViewMartix(m_camera->getViewMartix());
		setProjection(m_camera->getFov());
		updateMartix();
	}

	virtual void destroy() = 0;
	void setName(std::string v) { m_name = v; }
	std::string getName() { return m_name; }
	void setCamera(Camera* camera) { m_camera = camera; }
	Camera* getCamera() { return m_camera; }

protected:
	std::string m_name;
	Camera* m_camera;

	// ��������
	unsigned int loadTexture(std::string imgPath, int textureIndex) {
		// Texture ��ʼ��
		unsigned int texture;
		glActiveTexture(GL_TEXTURE0 + textureIndex); // ��������Ԫ
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// ����ͼƬ
		int width, height, nrChannels;
		unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
		/*
		��һ������: ָ��������Ŀ��(Target)������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
		�ڶ�������: Ϊ����ָ���༶��Զ����ļ��������ϣ�������ֶ�����ÿ���༶��Զ����ļ���Ļ�������������0��Ҳ���ǻ�������
		����������: ����OpenGL����ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ���������Ҳ��������ΪRGBֵ��
		���ĵ����: �������յ�����Ŀ�Ⱥ͸߶ȡ�����֮ǰ����ͼ���ʱ�򴢴������ǣ���������ʹ�ö�Ӧ�ı�����
		����������: Ӧ�����Ǳ���Ϊ0����ʷ���������⣩��
		���ߵڰ˸�: ����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
		�ھŸ�����: ��������ͼ�����ݡ�
		*/
		if (data) {
			if (imgPath.find(".png") != std::string::npos) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			printf("load texture failed.");
		}
		stbi_image_free(data);

		return texture;
	}

private:

};