#pragma once
#include <string>
#include <unordered_map>

struct ShaderSource
{
	const char* VertexSource;
	const char* FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_VertexShaderPath;
	std::string m_FragmentShaderPath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	ShaderSource m_ShaderSource;

public:
	Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	std::string ParseShader(std::string filename);
	bool CompileShader();
	void ComplieError(unsigned int shader, const char* type);
	int GetUniformLocation(const std::string& name);
};
