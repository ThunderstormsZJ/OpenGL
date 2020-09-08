#version 330 core					
layout(location = 0) in vec3 aPos;	
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

void main(){						
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   // Normal = aNormal;
   // Normal Martix Deal With
   Normal = mat3(transpose(inverse(view * model))) * aNormal;
   FragPos = vec3(view * model * vec4(aPos, 1.0));
   LightPos = vec3(view * vec4(lightPos, 1.0));
}									