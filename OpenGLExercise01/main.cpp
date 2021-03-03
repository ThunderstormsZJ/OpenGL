#include "Main.h"

// ʱ���
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

	ImGuiTool guiTool(window);
	Camera camera;
	camera.processMouseInput(window);
	Director::GetInstance().Init(window, &camera);
	
	// Scene
	Scene scene(guiTool);

	// GL �ǴӴ����ң� ���ϵ��µ�������ػ���
	while (!glfwWindowShouldClose(window))
	{
		// time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.processInput(window, deltaTime);
		guiTool.render();

		glClearColor(guiTool.ClearColor.x, guiTool.ClearColor.y, guiTool.ClearColor.z, guiTool.ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// scene
		scene.update(deltaTime);
		scene.render(deltaTime);
		
		guiTool.draw();

		glfwSwapBuffers(window); 
		glfwPollEvents();  // ��ȡ�����������
	}

	scene.destory();
	guiTool.destroy();

	glfwTerminate();
	return 0;
}