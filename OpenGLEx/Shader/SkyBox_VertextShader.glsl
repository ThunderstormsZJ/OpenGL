#version 330 core					
layout(location = 0) in vec3 aPos;	

out vec3 TexCoords; // 顶点坐标作为纹理坐标

uniform mat4 view;
uniform mat4 projection;

void main(){						
   TexCoords  = aPos;

   // mat4(mat3(view)): 将观察矩阵的位移分量给去除
   vec4 pos = projection * mat4(mat3(view)) * vec4(aPos, 1.0);

   // 设置深度缓冲值始终为最大1（z/w）
   // 配合glDepthFunc(GL_LEQUAL); 使得提前深度测试可以把不需要的片段提前丢弃
   gl_Position = pos.xyww;
}									