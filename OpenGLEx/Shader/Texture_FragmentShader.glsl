#version 330 core						
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

//uniform vec4 ourColor;		

// ����û��ʹ��glUniform��ֵ������Ϊ�����Ĭ������Ԫ��0
// ����Ҳ����ʹ��glActiveTexture����������Ԫ(OpenGl�ṩ��16������Ԫ�� 0~15)
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

// ��Ȳ������Ա任
float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}
// ��Ȳ������Ա任

void main(){							
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * vertexColor;

	vec4 tex1Color = texture(texture1, TexCoord);
	// ����͸������
	if (tex1Color.a < 0.1)
        discard;

	// �������������ǰ�������� �������Բ�ֵ�Ļ��
	// eg. 0.2: 80%�ĵ�һ��������ɫ��20%�ڶ���������ɫ���
	//FragColor = mix(tex1Color, texture(texture2, TexCoord * vec2(-1, 1)), mixValue);
	FragColor = tex1Color;
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0); // ���ֵ���ӻ�
}                                      
