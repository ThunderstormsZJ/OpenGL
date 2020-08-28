#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

class ImGuiTool
{
public:
	ImVec4 ClearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

	ImGuiTool(GLFWwindow* context);
	void init();
	void render();
	void draw();
	void destroy();
private:
	GLFWwindow* m_context;
};

