#include "WindowsWindow.h"
#include "imgui.h"
#include "stb_image.h"

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

bool WindowsWindow::s_GLFWInitialized = false;

static glm::mat4 proj = glm::ortho(0.0f, 1280.f, 0.0f, 720.0f, -1.0f, 1.0f);
static glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
static glm::vec3 translation(200, 200, 0);
static glm::mat4 model;

static glm::mat4 mvp;

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
	
	float positions[] = {
		-50.0f, -50.0f, 0.0f, 0.0f,
		 50.0f, -50.0f, 1.0f, 0.0f,
		 50.0f,  50.0f, 1.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Renderer = new Renderer;

	VAO = new VertexArray();
	Layout = new VertexBufferLayout();
	VBO = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	Layout->Push<float>(2);
	Layout->Push<float>(2);
	VAO->AddBuffer(VBO, Layout);

	IBO = new IndexBuffer(indices, 6);

	VAO->Bind();

	m_Shader = new Shader("shader/s1.vert", "shader/s1.frag");

	m_Texture = new Texture("res/texture/CStell2.png");
	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0);

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
	ImGui::Begin("Translation");
	ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1280.0f);
	ImGui::End();
	ImGui::Render();

	model = glm::translate(glm::mat4(1.0f), translation);
	mvp = proj * view * model;
	m_Renderer->Draw(VAO, VBO, m_Shader);

	m_Shader->SetUniformMat4f("u_MVP", mvp);


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
	delete IBO;
	delete VAO;
	delete Layout;
	delete m_Shader;
	delete m_Renderer;

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}