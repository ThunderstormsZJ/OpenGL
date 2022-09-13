// 片段着色器
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
        // 反相
        FragColor = vec4(vec3(1-texture(fboAttachment, TexCoords)), 1.0);
    }else if (PostProcessType == 2){
        // 灰度(取所有颜色分量平均化)
        FragColor = texture(fboAttachment, TexCoords);
        // float average = (FragColor.r + FragColor.g + FragColor.b)/3.0; // 平均化
        float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;  // 加权灰度
        FragColor = vec4(average,average,average,1.0);
    }else if (PostProcessType == 3){
        // 锐化
        float SharpenKernel[9] = float[](
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1
        );
        FragColor = CalKernel(SharpenKernel);
    }else if (PostProcessType == 4){
        // 模糊
        float BlurKernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16  
        );
        FragColor = CalKernel(BlurKernel);
    }else if (PostProcessType == 5){
        // 边缘检测
        float EdgeKernel[9] = float[](
            1, 1, 1,
            1, -8, 1,
            1, 1, 1
        );
        FragColor = CalKernel(EdgeKernel);
    }
}

vec4 CalKernel(float kernel[9]){
    // 附近9个区块的偏移值（会对这9个区块位置进行采样）
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
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