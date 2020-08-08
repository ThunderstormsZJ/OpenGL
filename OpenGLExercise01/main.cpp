#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//ͨ������STB_IMAGE_IMPLEMENTATION��Ԥ���������޸�ͷ�ļ�������ֻ������صĺ�������Դ�룬�����ǽ����ͷ�ļ���Ϊһ�� .cpp �ļ��ˡ�
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.h"
#include "Example.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//const float vertices[] = {
////  ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};
const float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indies[] = {
	2,1,0,
	0,3,2
};

// ʱ���
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// ��������
unsigned int setTexture(std::string imgPath, int textureIndex) {
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
	unsigned char *data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
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

int main() {
	/* 
	GLFW And GLEW RelationShip
		glfw��: ֧��OpenGL��OpenGL ES�����������ڣ���ȡ���룬�����¼���.��ΪOpenGLû�д��ڹ���Ĺ��ܣ����Ժܶ����ĵ���д�˹�����֧����Щ����.

		glew��: ��ͬ���Կ���˾��Ҳ�ᷢ��һЩֻ���Լ��Կ���֧ �ֵ���չ��������Ҫ�����������������ò�ȥѰ�����µ�glext.h,����GLEW��չ�⣬�����Ҳ����Ϊ�Ҳ��������Ľӿڶ����գ�
		��ΪGLEW���Զ�ʶ�����ƽ̨��֧�ֵ�ȫ��OpenGL�߼���չ������Ҳ����˵��ֻҪ����һ��glew.hͷ�ļ��������ʹ��gl,glu,glext,wgl,glx��ȫ������.
	*/
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open A Window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My First OpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window Failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit()!=GLEW_OK)
	{
		printf("Init Glew Failed.");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE); // �������޳�����
	//glCullFace(GL_FRONT);  // GL_BACK��ֻ�޳����� GL_FRONT��ֻ�޳����� GL_FRONT_AND_BACK���޳����������
	//glFrontFace(GL_CCW); // GL_CCW: ��ʱ�� GL_CW: ˳ʱ�� ��Ĭ����ʱ�룩
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// ����ģʽ

	// VAO��ʼ��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO��ʼ��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*
		GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
		GL_DYNAMIC_DRAW: the data is likely to change a lot.
		GL_STREAM_DRAW: the data will change every time it is drawn.
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO (Element Buffer Object) ��ʼ��
	// ��������
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indies), indies, GL_STATIC_DRAW);*/

	// Shader init
	Shader* shader = new Shader("Shader/VertextShader.glsl", "Shader/FragmentShader.glsl");
	
	// �˴�������ֵ0��ΧΪ[0-15]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	//// ��ɫ
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3  * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ����ͼƬ
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture1 = setTexture("Resources/container.jpg", 0);
	unsigned int texture2 = setTexture("Resources/awesomeface.png", 1);

	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	// Example
	Example example(shader, window);

	// GL �ǴӴ����ң� ���ϵ��µ�������ػ���
	while (!glfwWindowShouldClose(window))
	{
		// time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		example.update(deltaTime);
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		shader->use();

		//  ��ѭ���а��� ���ڶ��������Ƶ����
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		example.createCueBox();
		//glDrawElements(GL_TRIANGLES, sizeof(indies), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); 
		glfwPollEvents();  // ��ȡ�����������
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}