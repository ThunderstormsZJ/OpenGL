#include "Main.h"

// 时间差
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	/* 
	GLFW And GLEW RelationShip
		glfw库: 支持OpenGL及OpenGL ES，用来管理窗口，读取输入，处理事件等.因为OpenGL没有窗口管理的功能，所以很多热心的人写了工具来支持这些功能.

		glew库: 不同的显卡公司，也会发布一些只有自家显卡才支 持的扩展函数，你要想用这数涵数，不得不去寻找最新的glext.h,有了GLEW扩展库，你就再也不用为找不到函数的接口而烦恼，
		因为GLEW能自动识别你的平台所支持的全部OpenGL高级扩展函数。也就是说，只要包含一个glew.h头文件，你就能使用gl,glu,glext,wgl,glx的全部函数.
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
	//glEnable(GL_CULL_FACE); // 开启面剔除功能
	//glCullFace(GL_FRONT);  // GL_BACK：只剔除背面 GL_FRONT：只剔除正面 GL_FRONT_AND_BACK：剔除背面和正面
	//glFrontFace(GL_CCW); // GL_CCW: 逆时针 GL_CW: 顺时针 （默认逆时针）
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// 框线模式

	ImGuiTool guiTool(window);
	Camera camera;
	camera.processMouseInput(window);
	Director::GetInstance().Init(window, &camera);
	
	// Scene
	Scene scene(guiTool);

	// GL 是从从左到右， 从上到下的逐个像素绘制
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
		glfwPollEvents();  // 获取键盘鼠标输入
	}

	scene.destory();
	guiTool.destroy();

	glfwTerminate();
	return 0;
}