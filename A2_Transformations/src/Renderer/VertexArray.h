#pragma once

#include <cstdint>
#include "VertexBuffer.h"

static uint32_t m_VertexBufferIndex = 0;

class BufferLayout;

class VertexArray
{
private:
	uint32_t m_RendererID;
	mutable uint32_t m_BufferLayoutIndex = 0;

public:
	VertexArray();
	~VertexArray();

	//void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);
	void LinkAttrib(const VertexBuffer& vb, unsigned int index, const BufferLayout& layout, void* offset) const;
	void LinkAttrib(const VertexBuffer& vb, const BufferLayout& layout, void* offset) const;

	void Bind() const;
	void Unbind() const;
};

