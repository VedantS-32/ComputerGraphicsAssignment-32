#pragma once

#include <vector>
#include "glad/glad.h"

#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int index;
	unsigned int count;
	unsigned int type;
	unsigned char normalized;
	int stride;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;

public:
	VertexBufferLayout() {}

	template<typename T>
	void Push(unsigned int index, unsigned int count, int stride)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int index, unsigned int count, int stride)
	{
		m_Elements.push_back({ index, count, GL_FLOAT, GL_FALSE, stride });
	}

	template<>
	void Push<unsigned int>(unsigned int index, unsigned int count, int stride)
	{
		m_Elements.push_back({ index, count, GL_UNSIGNED_INT, GL_FALSE, stride });
	}

	template<>
	void Push<unsigned char>(unsigned int index, unsigned int count, int stride)
	{
		m_Elements.push_back({ index, count, GL_UNSIGNED_BYTE, GL_TRUE });
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
};

