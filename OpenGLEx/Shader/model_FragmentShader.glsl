#version 330 core
#extension GL_ARB_shading_language_include : require
#include "common_light_FragmentShader.glsl"

out vec4 FragColor;

in vec3 Normal;

void main(){
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(-FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 result;

	result += CalcDirLight(norm, viewDir);
	result += CalcPointLights(norm, viewDir);
	result += CalcSpotLight(norm, viewDir);

	FragColor = vec4(result, 1);
}
