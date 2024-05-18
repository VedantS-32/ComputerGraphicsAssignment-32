#include "TestTexture2D.h"

#include "imgui.h"
#include "Renderer/Renderer.h"

namespace test {
	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 100, 0), m_TranslationB(400, 300, 0),
		m_Proj(glm::ortho(0.0f, 1280.f, 0.0f, 720.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		m_Camera.setOrthographicProjection(-640.0f, 640.f, 360.0f, -360.0f, -500.0f, 500.0f);
		//m_Camera.setPerspectiveProjection(glm::radians(75.0f), (16.0f / 9.0f), -500.0f, 500.0f);

		m_Proj = m_Camera.GetProjection();

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

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 16 * sizeof(float));
		m_VertexArray = std::make_unique<VertexArray>();
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);


		BufferLayout layout;
		layout.Push<float>(0, 2, 4 * sizeof(float));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 0, layout, 0);
		layout.Push<float>(1, 2, 4 * sizeof(float));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 1, layout, (void*)(2 * sizeof(float)));

		m_Shader = std::make_unique<Shader>("shader/Texture2D.vert", "shader/Texture2D.frag");
		m_Texture = std::make_unique<Texture>("res/texture/CStell2.png");

		m_VertexArray->Bind();
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()
	{
		//Renderer renderer;
		Renderer::Clear();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		Renderer::Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, 6);

		m_Shader->SetUniformMat4f("u_MVP", mvp);

		model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		mvp = m_Proj * m_View * model;
		Renderer::Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, 6);

		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Translation");
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -320.0f, 320.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, -320.0f, 320.0f);
		ImGui::End();
	}
}