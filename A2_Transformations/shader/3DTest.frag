#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;


void main()
{
	FragColor = texture(u_Texture, v_TexCoord);
	//FragColor = vec4(v_TexCoord, 0.0, 1.0);
};