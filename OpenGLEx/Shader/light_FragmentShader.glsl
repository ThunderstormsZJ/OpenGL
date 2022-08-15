#version 330 core
#extension GL_ARB_shading_language_include : require
#include "common_light_FragmentShader.glsl"

out vec4 FragColor;

//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform float ambientStrenth = 1; // ������ǿ��
//uniform float specularStrenth = 1; // ����ǿ��
//uniform float specularShininess = 32; // �����
//uniform vec3 lightPos; // ��Դλ��
//uniform vec3 viewPos; // �۲���λ�� ��ת��Ϊ�۲�ռ�֮�� viewPosΪ��0,0,0��

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
