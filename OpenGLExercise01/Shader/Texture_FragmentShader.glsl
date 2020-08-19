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

void main(){							
	//FragColor = vertexColor;
	//FragColor = texture(ourTexture, TexCoord) * vertexColor;

	// 第三个参数会对前两个参数 进行线性插值的混合
	// eg. 0.2: 80%的第一个输入颜色和20%第二个输入颜色混合
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord * vec2(-1, 1)), mixValue);
}                                      
