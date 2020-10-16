#version 330 core						
out vec4 FragColor;

struct Material{
	//vec3 ambient; // 环境光颜色和漫反射一致
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission; // 自发光贴图
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
//uniform float ambientStrenth = 1; // 环境光强度
//uniform float specularStrenth = 1; // 镜面强度
//uniform float specularShininess = 32; // 反光度
//uniform vec3 lightPos; // 光源位置
//uniform vec3 viewPos; // 观察者位置 在转换为观察空间之后 viewPos为（0,0,0）

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
	vec3 reflectDir = reflect(-lightDir, norm); //  光源指向物体得方向
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	vec3 specular =  spec * light.specular * texture(material.specular, TexCoord).rgb;

	// mession
	vec3 mession = texture(material.emission, TexCoord).rgb;

	// result
	vec3 result = diffuse + ambient + specular + mession;

	FragColor = vec4(result, 1);
}                                      
