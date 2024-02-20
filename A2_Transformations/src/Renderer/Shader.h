#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderSource
{
	const char* VertexSource;
	const char* FragmentSource;
};

class Shader
{
private:
	std::string m_VertexShaderPath;
	std::string m_FragmentShaderPath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	ShaderSource m_ShaderSource;

public:
	unsigned int m_RendererID;
	Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	bool CompileShader();

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	std::string ParseShader(std::string filename);
	void ComplieError(unsigned int shader, const char* type);
	int GetUniformLocation(const std::string& name);
};
