#version 330 core						
out vec4 FragColor;

struct Material{
	//vec3 ambient; // ��������ɫ��������һ��
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission; // �Է�����ͼ
	int shininess;
};

// ���Դ
struct PointLight {
	int isOpen;
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// ƽ�й�
struct DirLight {
	int isOpen;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform float ambientStrenth = 1; // ������ǿ��
//uniform float specularStrenth = 1; // ����ǿ��
//uniform float specularShininess = 32; // �����
//uniform vec3 lightPos; // ��Դλ��
//uniform vec3 viewPos; // �۲���λ�� ��ת��Ϊ�۲�ռ�֮�� viewPosΪ��0,0,0��

in vec3 Normal;
in vec3 FragPos;
//in vec3 LightPos;
in vec2 TexCoord;
in mat4 ViewMat;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);

void main(){

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(-FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 result;

	if (dirLight.isOpen > 0){
		result += CalcDirLight(dirLight, norm, viewDir);
	}

	for(int i=0;i<NR_POINT_LIGHTS;i++){
		if (pointLights[i].isOpen > 0) {
			result += CalcPointLight(pointLights[i], norm, viewDir);
		}
	}

	// mession
	// vec3 mession = texture(material.emission, TexCoord).rgb;

	FragColor = vec4(result, 1);
}             

// ����ƽ�й�
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal); //  ��Դָ������÷���
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

	return (ambient + diffuse + specular);
}

// ���Դ
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir){
	vec3 lightPos = vec3(ViewMat * vec4(light.position, 1.0));
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	// ˥��
	float distance = length(lightPos - FragPos);
	float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

	return (ambient + diffuse + specular) * attenuation;
}
