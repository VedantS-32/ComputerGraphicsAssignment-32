#pragma once

#include "Renderer.h"

class Texture
{
public:
	unsigned int m_RendererID;
private:
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture() = default;
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	std::string GetFilePath() const { return m_FilePath; }

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};