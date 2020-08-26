#version 330 core						
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrenth = 0.1;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

void main(){
	// diffuse
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuse = max(dot(normalize(Normal), lightDir), 0);

	// ambient
	vec3 ambient = ambientStrenth * lightColor;

	// result
	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1);
}                                      
