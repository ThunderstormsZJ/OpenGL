#include "Main.h"
#include "Utils/OpenGLCommonAPI.h"
#include "Common/GlobalSettingCenter.hpp"

// 时间差
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 深度测试
	glEnable(GL_DEPTH_TEST); // 开启
	//glDepthFunc(GL_LESS);
	//glDepthFunc(GL_ALWAYS);  // 深度测试方法

	// 模板测试
	glEnable(GL_STENCIL_TEST);// 开启
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE); // 都通过时设置为ref值

	// 混合
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 面剔除
	glEnable(GL_CULL_FACE); // 开启面剔除功能
	glCullFace(GL_BACK);  // GL_BACK：只剔除背面 GL_FRONT：只剔除正面 GL_FRONT_AND_BACK：剔除背面和正面
	//glFrontFace(GL_CCW); // GL_CCW: 逆时针 GL_CW: 顺时针 （默认逆时针）
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// 框线模式
	
	//glEnable(GL_PROGRAM_POINT_SIZE); //修改点大小的功能

	OpenGLCommonAPI::PrintSupportExtensions();

	ImGuiTool guiTool(window);
	Camera camera;
	camera.processMouseInput(window);
	Director::GetInstance().Init(window, &camera, &guiTool);
	
	// Scene
	Scene scene;
	Director::GetInstance().SetRunScene(&scene);

	// GL 是从从左到右， 从上到下的逐个像素绘制
	while (!glfwWindowShouldClose(window))
	{
		if (GlobalSettingCenter::GetInstance().ShowPolygonLineMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (GlobalSettingCenter::GetInstance().CullFaceEnable) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}

		// time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.processInput(window, deltaTime);
		guiTool.render();

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