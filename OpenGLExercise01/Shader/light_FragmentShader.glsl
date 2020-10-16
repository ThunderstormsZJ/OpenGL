#version 330 core						
out vec4 FragColor;

struct Material{
	//vec3 ambient; // ��������ɫ��������һ��
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission; // �Է�����ͼ
	int shininess;
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
//uniform float ambientStrenth = 1; // ������ǿ��
//uniform float specularStrenth = 1; // ����ǿ��
//uniform float specularShininess = 32; // �����
//uniform vec3 lightPos; // ��Դλ��
//uniform vec3 viewPos; // �۲���λ�� ��ת��Ϊ�۲�ռ�֮�� viewPosΪ��0,0,0��

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoord;

void main(){
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	// diffuse
	vec3 diffuse = max(dot(norm, lightDir), 0) * light.diffuse * texture(material.diffuse, TexCoord).rgb;

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 viewDir = normalize(- FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); //  ��Դָ������÷���
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specular =  spec * light.specular * texture(material.specular, TexCoord).rgb;

	// mession
	vec3 mession = texture(material.emission, TexCoord).rgb;

	// result
	vec3 result = diffuse + ambient + specular + mession;

	FragColor = vec4(result, 1);
}                                      
