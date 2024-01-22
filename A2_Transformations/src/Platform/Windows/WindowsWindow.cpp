#include "WindowsWindow.h"
#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


bool WindowsWindow::s_GLFWInitialized = false;
static float CL[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

Window* Window::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

inline bool WindowsWindow::IsOpen()
{
	return glfwWindowshouldClose(m_Window);
}

void WindowsWindow::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Render ImGui
	ImGui::Begin("Clear Color");
	ImGui::ColorEdit4("Color", CL);
	ImGui::End();
	ImGui::Render();
	glViewport(0, 0, m_Data.Width, m_Data.Height);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void WindowsWindow::OnUpdate()
{
	
	glClearColor(CL[0], CL[1], CL[2], CL[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	Draw();

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void WindowsWindow::Init(WindowProps props)
{
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;
	m_Data.Title = props.Title;

	if (!s_GLFWInitialized)
	{
		glfwInit();
		s_GLFWInitialized = false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);

	gladLoadGL();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void WindowsWindow::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
