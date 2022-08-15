#include "OpenGLCommonAPI.h"
#include <GL/glew.h>

std::vector<std::string> OpenGLCommonAPI::g_supportExtensions = {};

void OpenGLCommonAPI::PrintSupportExtensions()
{
	std::vector<std::string> versionInfo = GetOpenGLVesionInfo();
	Logger.Instance->info("==================Header==================");
	for (size_t i = 0; i < versionInfo.size(); i++) {
		Logger.Instance->info(versionInfo[i]);
	}
	Logger.Instance->info("==================Header==================");

	GetSupportExtendsions();
	for (size_t i = 0; i < g_supportExtensions.size(); i++) {
		Logger.Instance->info("Exts: [{}]", g_supportExtensions[i].c_str());
	}
}

void OpenGLCommonAPI::GetSupportExtendsions()
{
	if (!g_supportExtensions.empty())
		return;

	GLint n, i;

	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (i = 0; i < n; i++) {
		std::string extension = (char*)glGetStringi(GL_EXTENSIONS, i);
		g_supportExtensions.push_back(extension);
	}
}

std::vector<std::string> OpenGLCommonAPI::GetOpenGLVesionInfo()
{
	std::vector<std::string> versionInfo = {};

	std::string Vendor(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	std::string Renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	std::string Version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	std::string ShadingLanguageVersion(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

	versionInfo.push_back("OpenGL Vendor: " + Vendor);
	versionInfo.push_back("OpenGL Renderer: " + Renderer);
	versionInfo.push_back("OpenGL Version: " + Version);
	versionInfo.push_back("OpenGL ShadingLanguageVersion: " + ShadingLanguageVersion);

	return versionInfo;
}
