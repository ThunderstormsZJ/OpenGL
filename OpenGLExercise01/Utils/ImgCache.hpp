#pragma once
#include "../stb_image.h"
#include "../Templates.h"
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
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if(nrChannels == 3)
				format = GL_RGB;
			else if(nrChannels == 4)
				format = GL_RGBA;


			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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