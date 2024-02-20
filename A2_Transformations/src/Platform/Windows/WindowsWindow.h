#pragma once

#include "Minimal.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Window.h"

class WindowsWindow : public Window
{
public:
	static bool s_GLFWInitialized;

	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	inline virtual void* GetNativeWindow() const { return m_Window; }

	inline bool IsOpen() override;
	void Input();
	virtual void OnUpdate() override;
	virtual void SwapBuffer() override;

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