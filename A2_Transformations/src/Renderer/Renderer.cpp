#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		print("[OpenGL Error]: " << std::hex << error << " " << function << " " << file << " : " << line);
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	GLCall(glClearColor(0.25, 0.25, 0.25, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const VertexBuffer& vb, const Shader& shader, unsigned int indicesCount)
{
	shader.Bind();
	va.Bind();
	vb.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr));

	shader.Unbind();
	va.Unbind();
	vb.Unbind();
}

void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<VertexBuffer>& vertexBuffer, uint32_t indexCount)
{
	vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
	vertexArray->Unbind();
}
