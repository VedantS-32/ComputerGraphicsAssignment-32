#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

static unsigned int s_VertexAttribLoc = 0;

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	//void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void LinkAttrib(const VertexBuffer& vb, unsigned int index, const VertexBufferLayout& layout, void* offset) const;

	void Bind() const;
	void Unbind() const;
};

