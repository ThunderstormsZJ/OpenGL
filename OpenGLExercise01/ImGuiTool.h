#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <functional>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "StructCollect.h"

#define NR_POINT_LIGHTS 4

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
	Material material = Material(32);
	std::vector<PointLight*> pointLights;
	DirLight dirLight = DirLight(new glm::vec3(1.0f), 0.05f, 0.4f, 0.5f);
	SpotLight spotLight = SpotLight(new glm::vec3(1.0f), 0, 1.0f, 1.0f);

	int pointLightCount = 0;

	ImGuiTool(GLFWwindow* context);
	void init();
	void render();
	void draw();
	void destroy();

	// callback
	void onPointLightChange(std::function<void(int)> callback);
private:
	GLFWwindow* m_context;

	// callback
	std::function<void(int)> pointLightChangeCallback;

	// 点光源位置
	std::vector<glm::vec3> pointLightPositions = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
};

