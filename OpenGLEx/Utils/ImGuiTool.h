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

class ImGuiTool;

class ImGuiTabItem {
public:
	std::string Label = "";

	ImGuiTabItem(std::string label) {
		this->Label = label;
	}

	virtual void Draw(ImGuiTool* tool) = 0;
};

class ImGuiTab
{
private:
	std::vector<ImGuiTabItem*> m_Items;
public:
	std::string Label = "";
	ImGuiTab(std::string label) {
		this->Label = label;
	}

	void AddItem(ImGuiTabItem* items) {
		m_Items.push_back(items);
	}

	void Draw(ImGuiTool* tool)
	{
		if (ImGui::BeginTabBar(Label.c_str()))
		{
			for (int i = 0; i < m_Items.size(); i++)
			{
				ImGuiTabItem* item = m_Items[i];
				if (ImGui::BeginTabItem(item->Label.c_str()))
				{
					item->Draw(tool);
					ImGui::EndTabItem();
				}

			}
			ImGui::EndTabBar();
		}
	}
};

class ImGuiTool
{
public:
	// base setting
	bool ShowPolygonLineMode = false;

	// secen setting
	glm::vec4 ClearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
	glm::vec3 ObjectColor = glm::vec3(1.0f, 0.5f, 0.31f);
	Material material;
	int PointLightCount = 0;

	// post process setting


	ImGuiTool(GLFWwindow* context);
	void init();
	void render();
	void draw();
	void destroy();

	// callback
	void onPointLightChange(std::function<void(int)> callback);
	std::function<void(int)> pointLightChangeCallback;

private:
	GLFWwindow* m_context;
	ImGuiTab* m_tab;
};

