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
		// Texture 初始化
		unsigned int texture;
		glGenTextures(1, &texture);

		// 加载图片
		int width, height, nrChannels;
		unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);

		/*
		第一个参数: 指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
		第二个参数: 为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
		第三个参数: 告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
		第四第五个: 设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
		第六个参数: 应该总是被设为0（历史遗留的问题）。
		第七第八个: 参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
		第九个参数: 是真正的图像数据。
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