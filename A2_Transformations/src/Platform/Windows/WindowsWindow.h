#pragma once

#include "Minimal.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

class WindowsWindow : public Window
{
public:
	VertexBuffer* VBO;
	IndexBuffer* IBO;
	VertexArray* VAO;
	VertexBufferLayout* Layout;
	Shader* m_Shader;
	Renderer* m_Renderer;
	Texture* m_Texture;

	static bool s_GLFWInitialized;

	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	inline bool IsOpen() override;
	void Draw();
	void OnUpdate() override;

private:
	void Init(WindowProps props);
	void Shutdown();

private:
	GLFWwindow* m_Window;

	struct WindowInfo
	{
		unsigned int Width = 640, Height = 640;
		std::string Title = "Default Name";
	};

	WindowInfo m_Data;
};