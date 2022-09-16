#pragma once
#include "Camera.h"
#include "Cube.h"
#include "LightCube.hpp"
#include "SykBox.hpp"
#include "Sphere.hpp"
#include "Model.h"
#include "../Common/GlobalSettingCenter.hpp"

#define MODE_TAG_LIGHT "LIGHT"
#define MODE_TAG_TRANSPARENT "TRANSPARENT"

class Scene
{
public:
	Scene()
	{
		this->m_tool = Director::GetInstance().GuiTool;
		this->m_FrameBuffEnable = GlobalSettingCenter::GetInstance().FrameBuffEnable;

		initEvent();
		this->CreateFrameBuffer();
		this->LoadSkyBox();

		//createTextureCueBox();
		//createLightCueBox();
		//createCubePanel(); 
		//createNanosuitModel(); // 模型
		createEnvironmentMapModel();
	}

	void createEnvironmentMapModel() {
		Shader shader("Shader/Skybox_Model_VertextShader.glsl", "Shader/Skybox_Model_FragmentShader.glsl");
		auto box = std::make_shared<Cube>(shader, CubeType::Box);
		box->SetCueMap(m_cubeMapId);
		addChild(box);
	}

	void createCubePanel() {
		Shader shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");

		auto panel = std::make_shared<Cube>(shader, CubeType::Panel);
		panel->SetPosition(glm::vec3(0));
		panel->SetTexture("Resources/metal.png", "texture1");
		addChild(panel);

		auto box = std::make_shared<Cube>(shader, CubeType::Box);
		box->SetPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
		box->SetTexture("Resources/container.jpg", "texture1", GL_CLAMP_TO_EDGE);
		addChild(box);
		
		box = std::make_shared<Cube>(shader, CubeType::Box);
		box->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
		box->SetTexture("Resources/container.jpg", "texture1", GL_CLAMP_TO_EDGE);
		addChild(box);

		// 草
		// transparent vegetation locations
		// --------------------------------
		std::vector<glm::vec3> vegetation
		{
			glm::vec3(-1.5f, 0.0f, -0.48f),
			glm::vec3(1.5f, 0.0f, 0.51f),
			glm::vec3(0.0f, 0.0f, 0.7f),
			glm::vec3(-0.3f, 0.0f, -2.3f),
			glm::vec3(0.5f, 0.0f, -0.6f)
		};

		//for (unsigned int i = 0; i < vegetation.size(); i++)
		//{
		//	auto vegetationCube = std::make_shared<Cube>(shader, CubeType::Transparent);
		//	vegetationCube->SetPosition(vegetation[i]);
		//	vegetationCube->SetTexture("Resources/blending_transparent_window.png", "texture1", GL_CLAMP_TO_EDGE);
		//	vegetationCube->SetTag(MODE_TAG_TRANSPARENT);
		//	addChild(vegetationCube);
		//}

		//for (unsigned int i = 0; i < vegetation.size(); i++)
		//{
		//	auto vegetationCube = std::make_shared<Cube>(shader, CubeType::Transparent);
		//	vegetationCube->SetPosition(vegetation[i]);
		//	vegetationCube->SetTexture("Resources/grass.png", "texture1", GL_CLAMP_TO_EDGE);
		//	addChild(vegetationCube);
		//}
	}

	void createNanosuitModel() {
		Shader shader("Shader/model_VertextShader.glsl", "Shader/model_FragmentShader.glsl");

		auto model = std::make_shared<Model>("Resources/nanosuit/nanosuit.obj", shader);
		addChild(model);
	}
	void createLightCueBox() {
		Shader shader("Shader/light_VertextShader.glsl", "Shader/light_FragmentShader.glsl");

		// box
		for (int i = 0; i < cubePositions.size(); i++)
		{
			auto box = std::make_shared<Cube>(shader);
			box->SetMaterial(&m_tool->material);
			box->SetPosition(cubePositions[i]);
			box->SetRotate(i * 10, i * 10, i * 10);
			box->SetTexture("Resources/container2.png", "material.texture_diffuse1");
			box->SetTexture("Resources/container2_specular.png", "material.texture_specular1");
			addChild(box);
		}
	}
	void createTextureCueBox() {
		// Shader init
		Shader shader("Shader/Texture_VertextShader.glsl", "Shader/Texture_FragmentShader.glsl");
		shader.setFloat("mixValue", 0.2f);

		for (int i = 0; i < cubePositions.size(); i++)
		{
			auto cube = std::make_shared<Cube>(shader);
			cube->GetShader()->setFloat("mixValue", 0.2f);
			cube->SetPosition(cubePositions[i]);
			cube->SetRotate(i * 10, i * 10, i * 10);
			cube->SetTexture("Resources/container.jpg", "texture1");
			cube->SetTexture("Resources/awesomeface.png", "texture2");
			addChild(cube);
		}
	}

	void initEvent() {
		// 监听点光源增加事件
		m_tool->onPointLightChange([=](int count) {
			removeChildrenByTag("lamp");

			std::vector<PointLight>* pointLights = Director::GetInstance().GetPPointLights();
			Shader shader("Shader/light_VertextShader.glsl", "Shader/light_lamp_FragmentShader.glsl");
			for (int i = 0; i < count; i++)
			{
				PointLight* light = &pointLights->at(i);
				auto lamp = std::make_shared<LightCube>(shader);
				lamp->SetScale(0.2f);
				lamp->SetTag("lamp");
				lamp->SetLight(light);
				addChild(lamp);
			}
		});
	}

	// 添加外部建模模型
	void addChild(std::shared_ptr<Node> model) {
		m_childrenModel.push_back(model);
	}

	void removeChildrenByTag(std::string tag) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end();) {
			if ((*begin)->GetTag() == tag) {
				begin = m_childrenModel.erase(begin);
			}
			else {
				++begin;
			}
		}
	}
	std::vector<std::shared_ptr<Node>> getChildrenByTag(std::string tag) {
		std::vector<std::shared_ptr<Node>> children;
		for (const auto &child : m_childrenModel) {
			if (child->GetTag() == tag) {
				children.push_back(child);
			}
		}

		return children;
	}
	std::shared_ptr<Node> getChildByName(std::string name) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++) 
		{
			if ((*begin)->GetName() == name) {
				return (*begin);
			}
		}

		return nullptr;
	}

	void render(float deltaTime) {
		// 进行一次排序
		// 透明物体从远到近绘制
		std::sort(m_childrenModel.begin(), m_childrenModel.end(), 
			[](std::shared_ptr<Node> nodeA, std::shared_ptr<Node> nodeB) {
				if (nodeA->GetTag() == MODE_TAG_TRANSPARENT && nodeB->GetTag() == MODE_TAG_TRANSPARENT) {
					glm::vec3 vecA = Director::GetInstance().MainCamera->getPos() - nodeA->GetPos();
					glm::vec3 vecB = Director::GetInstance().MainCamera->getPos() - nodeB->GetPos();

					return glm::length(vecA) > glm::length(vecB);
				}

				return false;
			}
		);

		if (fbo != 0)
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
		glClearColor(m_tool->ClearColor.x, m_tool->ClearColor.y, m_tool->ClearColor.z, m_tool->ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++)
		{
			(*begin)->Render();
		}

		this->CheckFrameBuffStatus();
		this->DisplayFramebufferTexture(mfbo_texture);
	}
	void update(float delataTime) {
		for (auto begin = m_childrenModel.begin(); begin != m_childrenModel.end(); begin++)
		{
			(*begin)->Update(delataTime);
		}
	}
	void destory() {
		// clear 后使用智能指针会自动调用析构函数销毁
		m_childrenModel.clear();

		glDeleteFramebuffers(1, &fbo);
	}

private:
	// 自定义帧缓冲
	bool m_FrameBuffEnable = false;
	unsigned int mfbo_VAO = 0;
	unsigned int mfbo_VBO;
	unsigned int mfbo_texture;
	Shader* mfbo_Shader;
	unsigned int fbo = 0;


	GLuint m_cubeMapId;
	std::vector<std::shared_ptr<Node>> m_childrenModel;
	ImGuiTool* m_tool;

	// 箱子位置
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f,  0.0f,  5.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	//float m_mixValue = 0;

	//void upDownMix() {
	//	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	//		m_mixValue -= 0.01;
	//	}
	//	else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	//	{
	//		m_mixValue += 0.01;
	//	}
	//	m_mixValue = m_mixValue > 1 ? 1 : m_mixValue;
	//	m_mixValue = m_mixValue < 0 ? 0 : m_mixValue;
	//	m_shader->setFloat("mixValue", m_mixValue);
	//}

	// 创建一个帧缓冲，并写入到纹理附件当中
	void CreateFrameBuffer() {
		if (!this->m_FrameBuffEnable)
			return;

		mfbo_Shader = new Shader("Shader/FBO_VertextShader.glsl", "Shader/FBO_FragmentShader.glsl");

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

#pragma region 纹理附件

		glGenTextures(1, &mfbo_texture);
		glBindTexture(GL_TEXTURE_2D, mfbo_texture);

		// 宽高为屏幕大小（这不是必须的）
		// pixels参数为Null， 我们仅仅分配了内存而没有填充它。
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mfbo_texture, 0);

#pragma endregion

#pragma region 深度和模板附件渲染缓冲对象

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

#pragma endregion

		// 检查
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Logger.Instance->error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// 绘制帧缓冲的纹理附件
	void DisplayFramebufferTexture(GLuint textureID)
	{
		if (!this->m_FrameBuffEnable) {
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认渲染
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 绘制一个四边形不需要深度测试
		glDisable(GL_DEPTH_TEST);

		if (mfbo_VAO == 0)
		{
			// 初始化
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &mfbo_VAO);
			glGenBuffers(1, &mfbo_VBO);
			glBindVertexArray(mfbo_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, mfbo_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		// 绘制纹理
		mfbo_Shader->use();
		mfbo_Shader->setInt("PostProcessType", GlobalSettingCenter::GetInstance().PostPrecessTypeValue);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBindVertexArray(mfbo_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void CheckFrameBuffStatus() {
		if (this->m_FrameBuffEnable != GlobalSettingCenter::GetInstance().FrameBuffEnable) {
			this->m_FrameBuffEnable = GlobalSettingCenter::GetInstance().FrameBuffEnable;

			// 关闭
			if (!this->m_FrameBuffEnable) {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glClear(GL_COLOR_BUFFER_BIT);
				glDeleteFramebuffers(1, &fbo);
				this->fbo = 0;
			}

			// 开启
			if (this->m_FrameBuffEnable) {
				this->CreateFrameBuffer();
			}
		}
	}

	void LoadSkyBox() {
		std::vector<std::string> faces {
			"Resources/skybox/right.jpg",
			"Resources/skybox/left.jpg",
			"Resources/skybox/top.jpg",
			"Resources/skybox/bottom.jpg",
			"Resources/skybox/front.jpg",
			"Resources/skybox/back.jpg"
		};

		// 加载贴图
		m_cubeMapId = ImgCache::GetInstance().addCubeMap(faces);
		Shader shader("Shader/SkyBox_VertextShader.glsl", "Shader/SkyBox_FragmentShader.glsl");

		auto box = std::make_shared<SkyBox>(shader, m_cubeMapId);

		this->addChild(box);
	}
};
