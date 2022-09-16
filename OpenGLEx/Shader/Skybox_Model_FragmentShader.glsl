#version 330 core
//#extension GL_ARB_shading_language_include : require
#include "common_light_FragmentShader.glsl"

out vec4 FragColor;

uniform vec3 cameraPos;

void main(){
	// Noraml �� FragPos ����ת���ڹ۲�����½��м���
	// ��Ϊ��պе�λ��Ӧ����ʼ�չ̶��ġ�
	vec3 norm = normalize(Normal);
	vec3 dir = normalize(FragPos - cameraPos);
	//vec3 result = CalcSkyBoxReflectEnvironmentMap(norm, dir);
	vec3 result = CalcSkyBoxRefractEnvironmentMap(norm, dir);

	FragColor = vec4(result, 1);
}
