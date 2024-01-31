#pragma once

#include "Minimal.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

#include "Test/TestClearColor.h"
#include "Test/TestTexture2D.h"

class WindowsWindow : public Window
{
public:
	test::Test* currentTest;
	test::TestMenu* testMenu;
	std::unique_ptr<test::TestMenu> testTexture;

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