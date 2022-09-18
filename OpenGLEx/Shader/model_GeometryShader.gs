#version 330 core
// 几何着色器
// 1. 爆炸效果
layout (triangles) in; // 输入三角形图元
layout (triangle_strip, max_vertices = 3) out; // 输出三角形图元

// 接收的是一个数组
// 对应图元点的数量
in VS_OUT {
    vec2 texCoords;
	vec3 normal;
	vec3 fragPos;
    mat4 viewMat;
} gs_in[];

out mat4 ViewMat;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
uniform float time;

// 获取每个面的法向量
vec3 GetNormal(){
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	
	return normalize(cross(a,b));
}

vec4 ExplodePos(vec4 position, vec3 normal){
	float speed = 2;
	vec3 dir = normal * ((sin(time) + 1)/2) * speed;
	return position + vec4(dir, 0);
}

// 爆炸效果
void Explode(){
	vec3 normal = GetNormal();
	gl_Position = ExplodePos(gl_in[0].gl_Position, normal);
	TexCoord = gs_in[0].texCoords;
	Normal = normal;
	ViewMat = gs_in[0].viewMat;
	FragPos = gs_in[0].fragPos;
	EmitVertex();
	gl_Position = ExplodePos(gl_in[1].gl_Position, normal);
	TexCoord = gs_in[1].texCoords;
	Normal = normal;
	ViewMat = gs_in[1].viewMat;
	FragPos = gs_in[1].fragPos;
	EmitVertex();
	gl_Position = ExplodePos(gl_in[2].gl_Position, normal);
	TexCoord = gs_in[2].texCoords;
	Normal = normal;
	ViewMat = gs_in[2].viewMat;
	FragPos = gs_in[2].fragPos;
	EmitVertex();
	EndPrimitive();
}

void main(){
	Explode();
}									