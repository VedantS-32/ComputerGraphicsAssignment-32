#version 450 core

layout(location = 0) out vec4 FragColor;

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_LightPosition;
in vec3 v_CameraPosition;
in vec3 v_ReflectedDir;

uniform sampler2D u_Texture;

uniform vec3 u_AmbientLight;
uniform float u_LightIntensity;
uniform vec4 u_LightColor;
uniform vec3 u_SpecularColor;
uniform float u_SpecularAlpha;

void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 reflected = normalize(v_Normal);
	float diffuse = max(dot(normal, v_LightPosition), 0.0);
	float phong = max(dot(reflected, v_CameraPosition), 0.0);
	vec3 halfAngle = (v_LightPosition + v_CameraPosition) / length(v_LightPosition + v_CameraPosition);
	float blinn = max(dot(normal, halfAngle), 0.0);

	//FragColor = vec4(1.0, 0.0, 0.0, 1.0) + (u_LightIntensity * vec4(u_SpecularColor, 1.0) * pow(blinn, u_SpecularAlpha)) + vec4(u_AmbientLight, 1.0);
	//FragColor = (u_LightIntensity * vec4(u_SpecularColor, 1.0) * pow(phong, u_SpecularAlpha)) + vec4(u_AmbientLight, 1.0);
	//FragColor = vec4(1.0, 1.0, 0.0, 1.0) * (u_LightIntensity * ((diffuse * u_LightColor) + ((vec4(u_SpecularColor, 1.0) * pow(blinn, u_SpecularAlpha)))) + vec4(u_AmbientLight, 1.0));
	FragColor = texture(u_Texture, v_TexCoord) * (u_LightIntensity * ((diffuse * u_LightColor) + ((vec4(u_SpecularColor, 1.0) * pow(blinn, u_SpecularAlpha)))) + vec4(u_AmbientLight, 1.0));
	//FragColor = vec4(0.1, 0.1, 0.1, 1.0) * (u_LightIntensity * ((diffuse * u_LightColor) + ((vec4(u_SpecularColor, 1.0) * pow(blinn, u_SpecularAlpha)))) + vec4(u_AmbientLight, 1.0));
	//FragColor = vec4(v_TexCoord, 0.0, 1.0);
	//FragColor = vec4(1.0, 1.0, 0.0, 1.0) * ((u_LightIntensity * diffuse * u_LightColor) + vec4(u_AmbientLight, 1.0));
	//FragColor = vec4(v_Normal, 1.0f);
};