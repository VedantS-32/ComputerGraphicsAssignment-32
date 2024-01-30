#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	int a = 12;
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};