#pragma once
#include "Templates.h"
#include <string>
#include <map>

class ImgCache : public Singleton<ImgCache>
{
public:
	unsigned int addTexture(std::string imgPath) {
		auto it = cache.find(imgPath);
		unsigned int texture = NULL;
		if (it != cache.end()) {
			texture = it->second;
		}
		else
		{
			texture = loadTexture(imgPath);

			cache[imgPath] = texture;
		}

		return texture;
	}

	unsigned int loadTexture(std::string imgPath) {
		// Texture ��ʼ��
		unsigned int texture;
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
	std::map<std::string, unsigned int> cache;
};