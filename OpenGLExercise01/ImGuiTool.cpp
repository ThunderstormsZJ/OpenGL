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

	// init field
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		PointLight* light = new PointLight(new glm::vec3(1.0f), 0.05f, 0.8f, 1.0f);
		light->Position = &pointLightPositions[i];
		pointLights.push_back(light);
	}
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
			ImGui::ColorEdit4("Clear Color", glm::value_ptr(ClearColor));
		}

		if (ImGui::CollapsingHeader("Model Config")) {
			ImGui::ColorEdit3("Model Color", glm::value_ptr(ObjectColor));
			if (ImGui::TreeNode("Material"))
			{
				ImGui::SliderInt("Shininess", &material.Shininess, 4, 248);
				ImGui::TreePop();
			}
		}

		if (ImGui::CollapsingHeader("Light Config")) {
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("PointLight"))
				{
					if (ImGui::Button("Add Point Light") && pointLightCount < NR_POINT_LIGHTS) {
						pointLightCount += 1;

						if (pointLightChangeCallback) {
							pointLightChangeCallback(pointLightCount);
						}
					}

					for (int i = 0; i < pointLightCount; i++)
					{
						char label[32]; sprintf_s(label, "Point Light[%d]", i + 1);
						if (ImGui::TreeNode(label)) {
							PointLight* pointLight = pointLights[i];
							ImGui::Checkbox("Open", &pointLight->IsOpen);

							ImGui::Separator();

							ImGui::SliderFloat3("Light Position", glm::value_ptr(*pointLight->Position), -1, 1);
							ImGui::SliderFloat("Constant", &pointLight->Constant, 0.0f, 1.0f, "constant(%.2f)");
							ImGui::SliderFloat("Linear", &pointLight->Linear, 0.0f, 1.0f, "linear(%.2f)");
							ImGui::SliderFloat("Quadratic", &pointLight->Quadratic, 0.0f, 2.0f, "quadratic(%.2f)");

							ImGui::Separator();

							ImGui::ColorEdit3("Light Color", glm::value_ptr(*pointLight->Color));
							ImGui::SliderFloat("Ambient", &pointLight->Ambient, 0.0f, 1.0f, "ambient(%.2f)");
							ImGui::SliderFloat("Diffuse", &pointLight->Diffuse, 0.0f, 1.0f, "diffuse(%.2f)");
							ImGui::SliderFloat("Specular", &pointLight->Specular, 0.0f, 1.0f, "specular(%.2f)");

							ImGui::TreePop();
						}

					}

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("DirLight"))
				{
					ImGui::Checkbox("Open", &dirLight.IsOpen);
					ImGui::Separator();

					ImGui::SliderFloat3("Light Direction", glm::value_ptr(*dirLight.Direction), -1, 1);

					ImGui::Separator();

					ImGui::ColorEdit3("Light Color", glm::value_ptr(*dirLight.Color));
					ImGui::SliderFloat("Ambient", &dirLight.Ambient, 0.0f, 1.0f, "ambient(%.2f)");
					ImGui::SliderFloat("Diffuse", &dirLight.Diffuse, 0.0f, 1.0f, "diffuse(%.2f)");
					ImGui::SliderFloat("Specular", &dirLight.Specular, 0.0f, 1.0f, "specular(%.2f)");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}

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

void ImGuiTool::onPointLightChange(std::function<void(int)> callback)
{
	pointLightChangeCallback = std::move(callback);
}
