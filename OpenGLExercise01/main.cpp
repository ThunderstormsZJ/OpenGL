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

//ͨ������STB_IMAGE_IMPLEMENTATION��Ԥ���������޸�ͷ�ļ�������ֻ������صĺ�������Դ�룬�����ǽ����ͷ�ļ���Ϊһ�� .cpp �ļ��ˡ�
#define STB_IMAGE_IMPLEMENTATION
#include "Scene.h"

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

unsigned int indies[] = {
	2,1,0,
	0,3,2
};

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
	//glEnable(GL_CULL_FACE); // �������޳�����
	//glCullFace(GL_FRONT);  // GL_BACK��ֻ�޳����� GL_FRONT��ֻ�޳����� GL_FRONT_AND_BACK���޳����������
	//glFrontFace(GL_CCW); // GL_CCW: ��ʱ�� GL_CW: ˳ʱ�� ��Ĭ����ʱ�룩
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// ����ģʽ

	// Scene
	Scene scene(window);

	// GL �ǴӴ����ң� ���ϵ��µ�������ػ���
	while (!glfwWindowShouldClose(window))
	{
		// Start ImGui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			//��ʼ����ImGui

			ImGui::Begin("IBinary Windows");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("IBinary Blog");
			//ImGui::SameLine();
			ImGui::Indent(); //����һ���Ʊ����ʼ����Button
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

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //�����ڻ�����Open֮����Ż���Imgui
		scene.update(deltaTime);
		scene.render(deltaTime);
		//glDrawElements(GL_TRIANGLES, sizeof(indies), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); 
		glfwPollEvents();  // ��ȡ�����������
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//scene.destory();

	glfwTerminate();
	return 0;
}