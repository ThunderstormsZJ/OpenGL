#version 330 core						
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrenth = 0.1; // 环境光强度
uniform float specularStrenth = 0.5; // 镜面强度
uniform float specularShininess = 32; // 反光度
//uniform vec3 lightPos; // 光源位置
//uniform vec3 viewPos; // 观察者位置 在转换为观察空间之后 viewPos为（0,0,0）

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main(){
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	// diffuse
	float diffuse = max(dot(norm, lightDir), 0);

	// ambient
	vec3 ambient = ambientStrenth * lightColor;

	// specular
	vec3 viewDir = normalize(- FragPos); // viewPos - FragPos => (0,0,0) - FragPos => -FragPos
	vec3 reflectDir = reflect(-lightDir, norm); //  光源指向物体得方向
	float spec = pow(max(dot(viewDir, reflectDir), 0), specularShininess);
	vec3 specular = specularStrenth * spec * lightColor;

	// result
	vec3 result = (diffuse + ambient + specular) * objectColor;

	FragColor = vec4(result, 1);
}                                      
