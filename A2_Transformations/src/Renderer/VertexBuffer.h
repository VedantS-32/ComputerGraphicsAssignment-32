#pragma once

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};


class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};