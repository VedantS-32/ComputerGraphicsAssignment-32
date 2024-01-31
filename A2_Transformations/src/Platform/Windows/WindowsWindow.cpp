#include "WindowsWindow.h"
#include "imgui.h"
#include "stb_image.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

bool WindowsWindow::s_GLFWInitialized = false;

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	currentTest = nullptr;
	testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
}


void WindowsWindow::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Test
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

	ImGui::Render();

	GLCall(glViewport(0, 0, m_Data.Width, m_Data.Height));
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void WindowsWindow::OnUpdate()
{
	GLCall(glClearColor(0.25, 0.25, 0.25, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Draw();

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


void WindowsWindow::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}