#include "Test3D.h"

#include "imgui.h"

static float rotation = 1.0f;

namespace test {
	Test3D::Test3D()
		: m_Translation(200, 100, 0),
		m_TranslationB(100, 50, 0),
		m_Proj(glm::ortho(0.0f, 1280.f, 0.0f, 720.0f, -1.0f, 1.0f)),
		m_Filepath("res/mesh/Cube.obj")
	{
		m_Camera.setOrthographicProjection(-640.0f, 640.f, 360.0f, -360.0f, -500.0f, 500.0f);
		m_Camera.setPerspectiveProjection(glm::radians(30.0f), (16.0f / 9.0f), -1000.0f, 1000.0f);

		m_Proj = m_Camera.GetProjection();

		//GLCall(glEnable(GL_BLEND));
		//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		//GLCall(glEnable(GL_DEPTH_TEST));

		// Vertices coordinates
		GLfloat vertices[] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-50.0f, 00.0f,  50.0f,   0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			-50.0f, 00.0f, -50.0f,   0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
			 50.0f, 00.0f, -50.0f,   0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			 50.0f, 00.0f,  50.0f,   0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
			 00.0f, 80.0f,  00.0f,   0.92f, 0.86f, 0.76f,	2.5f, 5.0f
		};

		// Indices for vertices order
		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
		};


		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 18);


		VertexBufferLayout layout;
		layout.Push<float>(0, 3, 8 * sizeof(float));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 0, layout, (void*)0);
		layout.Push<float>(1, 3, 8 * sizeof(float));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 1, layout, (void*)(3 * sizeof(float)));
		layout.Push<float>(2, 2, 8 * sizeof(float));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 2, layout, (void*)(6 * sizeof(float)));

		m_Shader = std::make_unique<Shader>("shader/3DTest.vert", "shader/3DTest.frag");
		m_Texture = std::make_unique<Texture>("res/texture/CStell2.png");

		m_VertexArray->Bind();
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	Test3D::~Test3D()
	{
	}
	void Test3D::OnUpdate(float deltaTime)
	{
		if (rotation >= 360.f)
			rotation = 0.0f;
		rotation += 0.5f;
	}
	void Test3D::OnRender()
	{
		Renderer renderer;
		renderer.Clear();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 0.0f));
		glm::mat4 mvp = m_Proj * m_View * model;
		//glm::mat4 mvp = glm::mat4(1.0);
		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, 18);

		m_Shader->SetUniformMat4f("u_MVP", mvp);
		//m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		model = glm::translate(glm::mat4(1.0f), m_TranslationB);
		mvp = m_Proj * m_View * model;
		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, 18);

		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
	void Test3D::OnImGuiRender()
	{
		ImGui::Begin("Translation");
		ImGui::SliderFloat3("TranslationA", &m_Translation.x, -640.0f, 640.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, -640.0f, 640.0f);
		ImGui::End();
	}
}
