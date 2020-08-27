#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

//通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，等于是将这个头文件变为一个 .cpp 文件了。
#define STB_IMAGE_IMPLEMENTATION
#include "Scene.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//const float vertices[] = {
////  ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

unsigned int indies[] = {
	2,1,0,
	0,3,2
};

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

	// Set ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Set Style
	ImGui::StyleColorsDark();
	// Bind OpenGL And Init
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

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

	// Scene
	Scene scene(window);

	// GL 是从从左到右， 从上到下的逐个像素绘制
	while (!glfwWindowShouldClose(window))
	{
		// Start ImGui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			//开始绘制ImGui

			ImGui::Begin("IBinary Windows");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("IBinary Blog");
			//ImGui::SameLine();
			ImGui::Indent(); //另起一行制表符开始绘制Button
			ImGui::Button("2222", ImVec2(100, 50));

			ImGui::End();
		}

		// Rendering
		ImGui::Render();

		// time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //必须在绘制完Open之后接着绘制Imgui
		scene.update(deltaTime);
		scene.render(deltaTime);
		//glDrawElements(GL_TRIANGLES, sizeof(indies), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); 
		glfwPollEvents();  // 获取键盘鼠标输入
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//scene.destory();

	glfwTerminate();
	return 0;
}