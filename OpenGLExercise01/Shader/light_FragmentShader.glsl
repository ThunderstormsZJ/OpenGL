#version 330 core
#extension GL_ARB_shading_language_include : require
#include "common_light_FragmentShader.glsl"

out vec4 FragColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform float ambientStrenth = 1; // 环境光强度
//uniform float specularStrenth = 1; // 镜面强度
//uniform float specularShininess = 32; // 反光度
//uniform vec3 lightPos; // 光源位置
//uniform vec3 viewPos; // 观察者位置 在转换为观察空间之后 viewPos为（0,0,0）

in vec3 Normal;
//in vec3 LightPos;

void main(){

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(-FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 result;

	result += CalcDirLight(norm, viewDir);
	result += CalcPointLights(norm, viewDir);
	result += CalcSpotLight(norm, viewDir);

	// mession
	// vec3 mession = texture(material.emission, TexCoord).rgb;

	FragColor = vec4(result, 1);
}
