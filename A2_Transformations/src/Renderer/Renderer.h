#pragma once

#include "Minimal.h"
#include "glad/glad.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const VertexBuffer& vb, const Shader& shader, unsigned int indicesCount) const;
};