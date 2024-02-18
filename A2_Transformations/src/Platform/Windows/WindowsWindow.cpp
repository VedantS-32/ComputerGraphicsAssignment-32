#include "WindowsWindow.h"

#include "imgui.h"
#include "stb_image.h"
#include "Renderer/Renderer.h"

#include "glfw/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

bool WindowsWindow::s_GLFWInitialized = false;
static int s_Projection = 1;

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

	GLFWimage images[1]{};
	images[0].pixels = stbi_load("res/texture/CStell2.png", &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(m_Window, 1, images);
	stbi_image_free(images[0].pixels);

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void WindowsWindow::Input()
{
	glfwPollEvents();
}

void WindowsWindow::OnUpdate()
{
	GLCall(glClearColor(0.25, 0.25, 0.25, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glViewport(0, 0, m_Data.Width, m_Data.Height));
	
	Input();
}

void WindowsWindow::SwapBuffer()
{
	glfwSwapBuffers(m_Window);
}


void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}