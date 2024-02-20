#include "Shader.h"
#include "Renderer.h"
#include "glad/glad.h"

#include <fstream>

Shader::Shader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
    : m_VertexShaderPath(VertexShaderPath), m_FragmentShaderPath(FragmentShaderPath), m_RendererID(0)
{
    CompileShader();
}

Shader::~Shader()
{
	Unbind();
	GLCall(glDeleteProgram(m_RendererID));
}

bool Shader::CompileShader()
{
	std::string vertexCode = ParseShader(m_VertexShaderPath);
	std::string fragmentCode = ParseShader(m_FragmentShaderPath);

	m_ShaderSource.VertexSource = vertexCode.c_str();
	m_ShaderSource.FragmentSource = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertexShader, 1, &m_ShaderSource.VertexSource, NULL));
	GLCall(glCompileShader(vertexShader));
	ComplieError(vertexShader, "Vertex Shader");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragmentShader, 1, &m_ShaderSource.FragmentSource, NULL));
	GLCall(glCompileShader(fragmentShader));
	ComplieError(fragmentShader, "Fragment Shader");

	m_RendererID = glCreateProgram();

	GLCall(glAttachShader(m_RendererID, vertexShader));
	GLCall(glAttachShader(m_RendererID, fragmentShader));

	GLCall(glLinkProgram(m_RendererID));
	ComplieError(m_RendererID, "Shader Program");

    return true;
}

void Shader::ComplieError(unsigned int shader, const char* type)
{
	int hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning uniform " << name << " doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
    return location;
}

std::string Shader::ParseShader(std::string filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}