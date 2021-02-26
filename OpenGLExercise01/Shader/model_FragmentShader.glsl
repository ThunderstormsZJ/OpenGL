#version 330 core						
out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse1;
};

uniform Material material;

in vec2 TexCoord;

void main(){
	FragColor = texture(material.texture_diffuse1, TexCoord);
}
