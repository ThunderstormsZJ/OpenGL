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

void main(){							
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * vertexColor;

	// �������������ǰ�������� �������Բ�ֵ�Ļ��
	// eg. 0.2: 80%�ĵ�һ��������ɫ��20%�ڶ���������ɫ���
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord * vec2(-1, 1)), mixValue);
}                                      
