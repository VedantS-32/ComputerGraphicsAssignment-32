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

void Renderer::Clear() const
{
	GLCall(glClearColor(0.25, 0.25, 0.25, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(VertexArray* va, VertexBuffer* vb, Shader* shader) const
{
	shader->Bind();
	va->Bind();
	vb->Bind();

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
