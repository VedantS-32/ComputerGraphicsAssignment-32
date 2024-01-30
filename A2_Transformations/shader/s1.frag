#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	FragColor = texColor;
	//FragColor = vec4(v_TexCoord, 0.0, 1.0);
};