#version 330 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

out vec4 vColor;

void main()
{
	gl_Position = vec4(aPosition, 1.0, 1.0);
	vColor = vec4(aColor, 1.0);
};