#include "VertexArray.h"
#include "BufferLayout.h"

#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	Bind();
}

VertexArray::~VertexArray()
{
	Unbind();
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::LinkAttrib(const VertexBuffer& vb, unsigned int index, const BufferLayout& layout, void* offset) const
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();

	const auto& element = elements[index];
	GLCall(glEnableVertexAttribArray(index));
	GLCall(glVertexAttribPointer(element.index, element.count, element.type, element.normalized,
		element.stride, offset));
}

void VertexArray::LinkAttrib(const VertexBuffer& vb, const BufferLayout& layout, void* offset) const
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();

	const auto& element = elements[m_BufferLayoutIndex];
	GLCall(glEnableVertexAttribArray(m_VertexBufferIndex));
	GLCall(glVertexAttribPointer(element.index, element.count, element.type, element.normalized,
		element.stride, offset));

	m_VertexBufferIndex++;
	m_BufferLayoutIndex++;
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
