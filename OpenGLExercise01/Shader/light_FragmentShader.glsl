#version 330 core						
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrenth = 0.1; // ������ǿ��
uniform float specularStrenth = 0.5; // ����ǿ��
uniform float specularShininess = 32; // �����
uniform vec3 lightPos; // ��Դλ��
uniform vec3 viewPos; // �۲���λ��

in vec3 Normal;
in vec3 FragPos;

void main(){
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	// diffuse
	float diffuse = max(dot(norm, lightDir), 0);

	// ambient
	vec3 ambient = ambientStrenth * lightColor;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); //  ��Դָ������÷���
	float spec = pow(max(dot(viewDir, reflectDir), 0), specularShininess);
	vec3 specular = specularStrenth * spec * lightColor;

	// result
	vec3 result = (ambient + specular) * objectColor;

	FragColor = vec4(result, 1);
}                                      
