#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 v_Color;
out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position =  u_MVP * vec4(aPosition, 1.0);
	v_TexCoord = aTexCoord;
	v_Color = aColor;
};