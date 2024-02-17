#include "Application.h"

#include <Input.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;
	m_Window = std::unique_ptr<Window>(Window::Create(WindowProps()));
	
	m_ImGuiLayer = std::make_unique<ImGuiLayer>();

	currentTest = nullptr;
	testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
	testMenu->RegisterTest<test::TestModel3D>("3D Model");
	testMenu->RegisterTest<test::Test3D>("3D Test");
}

Application::~Application()
{
	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;
}

void Application::Run()
{
	while (!m_Window->IsOpen())
	{
		m_Window->OnUpdate();
		m_ImGuiLayer->Begin();
		m_ImGuiLayer->OnImGuiRender();
		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}
		m_ImGuiLayer->End();

		m_Window->SwapBuffer();
	}
}
