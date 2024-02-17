#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 v_Normal;
in vec2 v_TexCoord;

void main()
{
	FragColor = vec4(0.0, 1.0, 1.0, 1.0);
};