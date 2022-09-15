#version 330 core					
layout(location = 0) in vec3 aPos;	

out vec3 TexCoords; // ����������Ϊ��������

uniform mat4 view;
uniform mat4 projection;

void main(){						
   TexCoords  = aPos;

   // mat4(mat3(view)): ���۲�����λ�Ʒ�����ȥ��
   vec4 pos = projection * mat4(mat3(view)) * vec4(aPos, 1.0);

   // ������Ȼ���ֵʼ��Ϊ���1��z/w��
   // ���glDepthFunc(GL_LEQUAL); ʹ����ǰ��Ȳ��Կ��԰Ѳ���Ҫ��Ƭ����ǰ����
   gl_Position = pos.xyww;
}									