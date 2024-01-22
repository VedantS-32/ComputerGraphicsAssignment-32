#pragma once

#include "Minimal.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

class WindowsWindow : public Window
{
public:
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
		unsigned int Width, Height;
		std::string Title;
	};

	WindowInfo m_Data;
};
