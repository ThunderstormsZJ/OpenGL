#version 330 core						
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

//uniform vec4 ourColor;		

// 我们没有使用glUniform赋值，是因为纹理的默认纹理单元是0
// 我们也可以使用glActiveTexture激活多个纹理单元(OpenGl提供了16个纹理单元： 0~15)
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

// 深度测试线性变换
float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}
// 深度测试线性变换

void main(){							
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * vertexColor;

	vec4 tex1Color = texture(texture1, TexCoord);
	// 丢弃透明部分
	if (tex1Color.a < 0.1)
        discard;

	// 第三个参数会对前两个参数 进行线性插值的混合
	// eg. 0.2: 80%的第一个输入颜色和20%第二个输入颜色混合
	//FragColor = mix(tex1Color, texture(texture2, TexCoord * vec2(-1, 1)), mixValue);
	FragColor = tex1Color;
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0); // 深度值可视化
}                                      
