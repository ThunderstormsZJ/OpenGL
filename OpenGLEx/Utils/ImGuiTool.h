#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <functional>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Common/StructCollect.h"
#include "../Render/Director.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


class ImGuiTool
{
public:
	glm::vec4 ClearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
	glm::vec3 ObjectColor = glm::vec3(1.0f, 0.5f, 0.31f);
	Material material;

	ImGuiTool(GLFWwindow* context);
	void init();
	void render();
	void draw();
	void destroy();

	// callback
	void onPointLightChange(std::function<void(int)> callback);
private:
	GLFWwindow* m_context;
	int pointLightCount = 0;

	// callback
	std::function<void(int)> pointLightChangeCallback;
};

