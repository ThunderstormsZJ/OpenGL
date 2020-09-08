#version 330 core						
out vec4 FragColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
//uniform vec3 objectColor;
//uniform vec3 lightColor;
uniform float ambientStrenth = 1; // ������ǿ��
uniform float specularStrenth = 1; // ����ǿ��
uniform float specularShininess = 32; // �����
//uniform vec3 lightPos; // ��Դλ��
//uniform vec3 viewPos; // �۲���λ�� ��ת��Ϊ�۲�ռ�֮�� viewPosΪ��0,0,0��

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main(){
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	// diffuse
	vec3 diffuse = max(dot(norm, lightDir), 0) * material.diffuse * light.diffuse;

	// ambient
	vec3 ambient = ambientStrenth * material.ambient * light.ambient;

	// specular
	vec3 viewDir = normalize(- FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); //  ��Դָ������÷���
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specular = specularStrenth * spec * material.specular * light.specular;

	// result
	vec3 result = diffuse + ambient + specular;

	FragColor = vec4(result, 1);
}                                      
