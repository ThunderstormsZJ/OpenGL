#include "ImGuiTool.h"

ImGuiTool::ImGuiTool(GLFWwindow* context):m_context(context)
{
	init();
}

void ImGuiTool::init()
{
	// Set ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Set Style
	ImGui::StyleColorsDark();
	// Bind OpenGL And Init
	ImGui_ImplGlfw_InitForOpenGL(m_context, true);
	ImGui_ImplOpenGL3_Init();
}

void ImGuiTool::render()
{
	// Start ImGui Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		//Content
		ImGui::Begin("OpenGL Tools");

		if (ImGui::CollapsingHeader("Windows Config")) {
			ImGui::ColorEdit4("Clear Color", (float*)&ClearColor);
		}

		if (ImGui::CollapsingHeader("Model Config")) {
			ImGui::ColorEdit3("Color", glm::value_ptr(ObjectColor));
		}

		if (ImGui::CollapsingHeader("Light Config")) {
			//ImGui::ColorEdit4("Color", (float*)&ClearColor);
		}

		ImGui::End();
	}

	// Rendering
	ImGui::Render();
}

void ImGuiTool::draw()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //必须在绘制完Open之后接着绘制Imgui
}

void ImGuiTool::destroy()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
