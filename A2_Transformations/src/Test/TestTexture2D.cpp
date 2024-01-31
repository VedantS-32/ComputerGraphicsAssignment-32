#include "TestTexture2D.h"

#include "imgui.h"

namespace test {
	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 100, 0), m_TranslationB(400, 300, 0),
		  m_Proj(glm::ortho(0.0f, 1280.f, 0.0f, 720.0f, -1.0f, 1.0f)),
		  m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
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
		
		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 16 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("shader/s1.vert", "shader/s1.frag");
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
		Renderer renderer;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader);

		m_Shader->SetUniformMat4f("u_MVP", mvp);

		model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		mvp = m_Proj * m_View * model;
		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader);

		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Translation");
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 1280.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 1280.0f);
		ImGui::End();
	}
}