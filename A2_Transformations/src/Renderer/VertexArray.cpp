#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
									 layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout, unsigned int offset)
{
	Bind();
	vb->Bind();
	const auto& elements = layout->GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
			layout->GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	//const auto& element = elements[s_VertexAttribLoc];
	//GLCall(glEnableVertexAttribArray(s_VertexAttribLoc));
	//GLCall(glVertexAttribPointer(s_VertexAttribLoc, element.count, element.type, element.normalized,
	//	layout->GetStride(s_VertexAttribLoc), (const void*)offset));
	//offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

	//s_VertexAttribLoc++;
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
