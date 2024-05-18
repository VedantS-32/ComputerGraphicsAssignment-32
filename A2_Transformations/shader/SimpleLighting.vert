#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_LightPosition;
out vec3 v_CameraPosition;
out vec3 v_ReflectedDir;

uniform mat4 u_MVP;
uniform mat4 u_ModelView;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Normal = normalize(mat3(transpose(inverse(u_ModelView))) * a_Normal);
	v_LightPosition = normalize(u_LightPosition);
	v_CameraPosition = normalize(u_CameraPosition);
	v_ReflectedDir = reflect(-v_LightPosition, v_Normal);
	gl_Position = u_MVP * vec4(a_Position, 1.0);
};