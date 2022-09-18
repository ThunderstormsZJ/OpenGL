#version 330 core					
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
    vec2 texCoords;
    vec3 normal;
    vec3 fragPos;
    mat4 viewMat;
} vs_out;

out mat4 ViewMat;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main(){				
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   Normal = mat3(transpose(inverse(view * model))) * aNormal;
   FragPos = vec3(view * model * vec4(aPos, 1.0));
   ViewMat = view;
   TexCoord = aTexCoord;

   vs_out.texCoords = aTexCoord;
   vs_out.normal = Normal;
   vs_out.fragPos = FragPos;
   vs_out.viewMat = view;
}									