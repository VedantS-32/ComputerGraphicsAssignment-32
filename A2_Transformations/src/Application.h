#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Window.h"
#include "Editor.h"
#include "ImGui/ImGuiLayer.h"

#include "Test/TestClearColor.h"
#include "Test/TestTexture2D.h"
#include "Test/TestModel3D.h"
#include "Test/Test3D.h"
#include "Test/SimpleLighting.h"

#include <memory>

class Application
{
public:
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<Editor> m_Editor;
	std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

	test::Test* currentTest;
	test::TestMenu* testMenu;
	std::unique_ptr<test::TestMenu> testTexture;

	Application();
	~Application();
	void Run();

	inline Window& GetWindow() const { return *m_Window; }
	static inline Application& Get() { return *s_Instance; }

private:
	static Application* s_Instance;
};