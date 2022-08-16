struct Material{
	//vec3 ambient; // ��������ɫ��������һ��
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_height1;

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

// �۹�
struct SpotLight {
	int isOpen;
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

in mat4 ViewMat;
in vec2 TexCoord;
in vec3 FragPos;

// function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

// ����ƽ�й�
vec3 CalcDirLight(vec3 normal, vec3 viewDir){
	DirLight light = dirLight;
	if (light.isOpen <= 0){
		return vec3(0,0,0);
	}

	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal); //  ��Դָ������÷���
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoord).rgb;

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

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoord).rgb;

	return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcPointLights(vec3 normal, vec3 viewDir){
	vec3 result;

	for(int i=0;i<NR_POINT_LIGHTS;i++){
		if (pointLights[i].isOpen > 0) {
			result += CalcPointLight(pointLights[i], normal, viewDir);
		}
	}

	return result;
}

// �۹��
vec3 CalcSpotLight(vec3 normal, vec3 viewDir){
	SpotLight light = spotLight;
	if (light.isOpen <= 0){
		return vec3(0,0,0);
	}

	vec3 lightDir = normalize(-FragPos);

	// �������
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoord).rgb;

	// ˥��
	float distance = length(-FragPos);
	float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// Smooth Edge
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

	// ���Ի�����������
	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular) * attenuation;
}
