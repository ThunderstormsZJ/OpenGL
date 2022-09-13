// Ƭ����ɫ��
#version 330 core
out vec4 FragColor;
in  vec2 TexCoords;

uniform sampler2D fboAttachment;
uniform int PostProcessType = 0;

const float offset = 1.0 / 300.0; 

vec4 CalKernel(float kernel[9]);

void main()
{
    if (PostProcessType == 0){
        FragColor = texture(fboAttachment, TexCoords);
    }else if (PostProcessType == 1){
        // ����
        FragColor = vec4(vec3(1-texture(fboAttachment, TexCoords)), 1.0);
    }else if (PostProcessType == 2){
        // �Ҷ�(ȡ������ɫ����ƽ����)
        FragColor = texture(fboAttachment, TexCoords);
        // float average = (FragColor.r + FragColor.g + FragColor.b)/3.0; // ƽ����
        float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;  // ��Ȩ�Ҷ�
        FragColor = vec4(average,average,average,1.0);
    }else if (PostProcessType == 3){
        // ��
        float SharpenKernel[9] = float[](
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1
        );
        FragColor = CalKernel(SharpenKernel);
    }else if (PostProcessType == 4){
        // ģ��
        float BlurKernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16  
        );
        FragColor = CalKernel(BlurKernel);
    }else if (PostProcessType == 5){
        // ��Ե���
        float EdgeKernel[9] = float[](
            1, 1, 1,
            1, -8, 1,
            1, 1, 1
        );
        FragColor = CalKernel(EdgeKernel);
    }
}

vec4 CalKernel(float kernel[9]){
    // ����9�������ƫ��ֵ�������9������λ�ý��в�����
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // ����
        vec2( 0.0f,    offset), // ����
        vec2( offset,  offset), // ����
        vec2(-offset,  0.0f),   // ��
        vec2( 0.0f,    0.0f),   // ��
        vec2( offset,  0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2( 0.0f,   -offset), // ����
        vec2( offset, -offset)  // ����
    );

    vec3 sampleTex[9];
    for (int i=0; i<9; i++){
        sampleTex[i] = vec3(texture(fboAttachment, TexCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i=0; i<9; i++){
        col += kernel[i] * sampleTex[i];
    }

    return vec4(col, 1.0);
}