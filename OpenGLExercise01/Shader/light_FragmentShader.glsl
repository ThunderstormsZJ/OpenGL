#version 330 core						
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrenth = 0.1;

void main(){
	vec3 ambient = ambientStrenth * lightColor;
	vec3 result = ambient * objectColor;

	FragColor = vec4(result, 1);
}                                      
