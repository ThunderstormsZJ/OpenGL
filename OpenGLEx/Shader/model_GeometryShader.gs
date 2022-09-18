#version 330 core
// ������ɫ��
// 1. ��ըЧ��
layout (triangles) in; // ����������ͼԪ
layout (triangle_strip, max_vertices = 3) out; // ���������ͼԪ

// ���յ���һ������
// ��ӦͼԪ�������
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

// ��ȡÿ����ķ�����
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

// ��ըЧ��
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