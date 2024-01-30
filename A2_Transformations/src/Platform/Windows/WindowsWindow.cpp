#include "WindowsWindow.h"
#include "imgui.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

bool WindowsWindow::s_GLFWInitialized = false;
static float CL[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
static GLfloat CT[4] = { 0.9f, 0.3f, 0.5f, 1.0f };

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	m_Renderer = new Renderer;

	VAO = new VertexArray();
	Layout = new VertexBufferLayout();
	VBO = new VertexBuffer(positions, 8 * sizeof(float));

	Layout->Push<float>(2);
	VAO->AddBuffer(VBO, Layout);

	IBO = new IndexBuffer(indices, 6);

	ColorBuffer = new VertexBuffer(color, sizeof(color));

	Layout->Push<float>(3);
	VAO->AddBuffer(ColorBuffer, Layout);
	VAO->Bind();

	m_Shader = new Shader("s1.vert", "s1.frag");

	VBO->Unbind();
	//IBO->Unbind();
	VAO->Unbind();
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

	m_Renderer->Draw(VAO, VBO, m_Shader);

	GLCall(glViewport(0, 0, m_Data.Width, m_Data.Height));
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void WindowsWindow::OnUpdate()
{
	m_Renderer->Clear();

	Draw();

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}


void WindowsWindow::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete VBO;
	delete ColorBuffer;
	delete IBO;
	delete VAO;
	delete Layout;
	delete m_Shader;
	delete m_Renderer;

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}