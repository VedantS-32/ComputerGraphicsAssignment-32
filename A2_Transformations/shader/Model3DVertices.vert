#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 v_Normal;
out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position =  u_MVP * vec4(aPosition, 1.0);
	gl_PointSize = 5.0;
	v_TexCoord = aTexCoord;
	v_Normal = aNormal;
};