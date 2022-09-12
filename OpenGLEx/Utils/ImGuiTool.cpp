#include "ImGuiTool.h"

ImGuiTool::ImGuiTool(GLFWwindow* context) :m_context(context)
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

	ImGuiIO io = ImGui::GetIO();

	// 字体
	io.Fonts->AddFontFromFileTTF("Resources/fonts/WenDaoLingFeiXiaoKai-2.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
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

		if (ImGui::Checkbox(u8"线框模式", &ShowPolygonLineMode)) {

		}

		if (ImGui::CollapsingHeader("Windows Config")) {
			ImGui::ColorEdit4("Clear Color", glm::value_ptr(ClearColor));
		}

		if (ImGui::CollapsingHeader("Cube Config")) {
			ImGui::ColorEdit3("Color", glm::value_ptr(ObjectColor));
		}

		if (ImGui::CollapsingHeader("Material Config")) {
			ImGui::SliderInt("Shininess", &material.Shininess, 4, 248);
		}

		if (ImGui::CollapsingHeader("Light Config")) {
			if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("PointLight"))
				{
					std::vector<PointLight>* pointLights = Director::GetInstance().GetPPointLights();
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
							PointLight* pointLight = &pointLights->at(i);
							ImGui::Checkbox("Open", &pointLight->IsOpen);

							ImGui::Separator();

							ImGui::SliderFloat3("Light Position", glm::value_ptr(pointLight->Position), -1, 1);
							ImGui::SliderFloat("Constant", &pointLight->Constant, 0.0f, 1.0f, "constant(%.2f)");
							ImGui::SliderFloat("Linear", &pointLight->Linear, 0.0f, 1.0f, "linear(%.2f)");
							ImGui::SliderFloat("Quadratic", &pointLight->Quadratic, 0.0f, 2.0f, "quadratic(%.2f)");

							ImGui::Separator();

							ImGui::ColorEdit3("Light Color", glm::value_ptr(pointLight->Color));
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
					DirLight* dirLight = Director::GetInstance().GetPDirLight();
					ImGui::Checkbox("Open", &dirLight->IsOpen);
					ImGui::Separator();

					ImGui::SliderFloat3("Light Direction", glm::value_ptr(dirLight->Direction), -1, 1);

					ImGui::Separator();

					ImGui::ColorEdit3("Light Color", glm::value_ptr(dirLight->Color));
					ImGui::SliderFloat("Ambient", &dirLight->Ambient, 0.0f, 1.0f, "ambient(%.2f)");
					ImGui::SliderFloat("Diffuse", &dirLight->Diffuse, 0.0f, 1.0f, "diffuse(%.2f)");
					ImGui::SliderFloat("Specular", &dirLight->Specular, 0.0f, 1.0f, "specular(%.2f)");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("SpotLight"))
				{
					SpotLight* spotLight = Director::GetInstance().GetPSpotLight();
					Camera* camera = Director::GetInstance().MainCamera;
					ImGui::Checkbox("Open", &spotLight->IsOpen);
					ImGui::Separator();

					spotLight->Position = camera->getPos(); // update spotLight position
					ImGui::Text("Position (%.2f, %.2f, %.2f)", spotLight->Position.x, spotLight->Position.y, spotLight->Position.z);
					ImGui::Text("Direction (%.2f, %.2f, %.2f)", spotLight->Direction.x, spotLight->Direction.y, spotLight->Direction.z);
					ImGui::SliderAngle("Light CutOff", &spotLight->CutOffRad, 0, 60);
					ImGui::SliderFloat("Light Smooth Intensity", &spotLight->SmoothEdgeIntensity, 0, 10);
					ImGui::SliderFloat("Constant", &spotLight->Constant, 0.0f, 1.0f, "constant(%.2f)");
					ImGui::SliderFloat("Linear", &spotLight->Linear, 0.0f, 1.0f, "linear(%.2f)");
					ImGui::SliderFloat("Quadratic", &spotLight->Quadratic, 0.0f, 2.0f, "quadratic(%.2f)");

					ImGui::Separator();

					ImGui::ColorEdit3("Light Color", glm::value_ptr(spotLight->Color));
					ImGui::SliderFloat("Ambient", &spotLight->Ambient, 0.0f, 1.0f, "ambient(%.2f)");
					ImGui::SliderFloat("Diffuse", &spotLight->Diffuse, 0.0f, 1.0f, "diffuse(%.2f)");
					ImGui::SliderFloat("Specular", &spotLight->Specular, 0.0f, 1.0f, "specular(%.2f)");
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
