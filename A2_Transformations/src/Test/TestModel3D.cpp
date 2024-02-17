#include "TestModel3D.h"

#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

static float rotation = 1.0f;
static glm::mat4 model;
static int s_Projection = 1;
static bool pressed = false;
static bool pressed1 = false;

static std::string projection = "Perspective Projection";

namespace test {
	TestModel3D::TestModel3D()
		: m_Translation(0.0f, -10.0f, -20.0f),
		m_Filepath("res/mesh/Teapot.obj"),
		m_ClearColor { 0.25f, 0.2f, 0.25f, 1.0f }
	{
		m_Model = std::make_unique<Model>();

		if (m_Model->loadModel(m_Filepath.c_str()) != 0) {
			print("Failed to load 3D Model");
		}

		//m_Camera.setOrthographicProjection(-16.0f, 16.0f, 9.0f, -9.0f, -500.0f, 500.0f);
		m_Camera.setPerspectiveProjection(glm::radians(30.0f), (16.0f / 9.0f), -1000.0f, 1000.0f);

		m_Proj = m_Camera.GetProjection();

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(&m_Model->getVertices()[0], m_Model->getVertices().size() * sizeof(Vertex));
		m_IndexBuffer = std::make_unique<IndexBuffer>(&m_Model->getIndices()[0], m_Model->getIndices().size());

		m_VertexArray->Bind();

		VertexBufferLayout layout;
		layout.Push<float>(0, 3, sizeof(Vertex));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 0, layout, (void*)0);
		layout.Push<float>(1, 3, sizeof(Vertex));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 1, layout, (void*)offsetof(Vertex, m_normal));
		layout.Push<float>(2, 2, sizeof(Vertex));
		m_VertexArray->LinkAttrib(*m_VertexBuffer, 2, layout, (void*)offsetof(Vertex, m_texcoords));


		m_Shader = std::make_unique<Shader>("shader/Model3DVertices.vert", "shader/Model3DVertices.frag");
		m_Texture = std::make_unique<Texture>("res/texture/CStell2.png");

		m_Texture->Bind();
		m_Shader->Bind();
		//m_Shader->SetUniform1i("u_Texture", 0);

		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		glPointSize(2.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	TestModel3D::~TestModel3D()
	{
	}

	void TestModel3D::OnUpdate(float deltaTime)
	{
		Input();

		if (rotation >= 360.f)
			rotation = 0.0f;
		rotation += 0.1f;
	}
	void TestModel3D::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;
		model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, m_IndexBuffer->GetCount() * sizeof(unsigned int));
	}

	void TestModel3D::Input()
	{
		auto key = Input::IsKeyPressed(GLFW_KEY_P);
		if (key == 1 && pressed == false)
		{
			if (s_Projection)
			{
				projection = "Orthographic Projection";
				print(projection);
				m_Camera.setOrthographicProjection(-32.0f, 32.0f, 18.0f, -18.0f, -500.0f, 500.0f);
				m_Proj = m_Camera.GetProjection();
				s_Projection = 0;
			}
			else
			{
				projection = "Perspective Projection";
				print(projection);
				m_Camera.setPerspectiveProjection(glm::radians(30.0f), (16.0f / 9.0f), -1000.0f, 1000.0f);
				m_Proj = m_Camera.GetProjection();
				s_Projection = 1;
			}
			pressed = true;
		}
		if (key == 0)
		{
			pressed = false;
		}

		auto key1 = Input::IsKeyPressed(GLFW_KEY_F6);
		if (key1 == 1 && pressed1 == false)
		{
			print("Recompiling Shaders");
			if (m_Shader->CompileShader())
				print("Shaders Recompiled Successfully");
			pressed1 = true;
		}
		if (key1 == 0)
		{
			pressed1 = false;
		}
	}

	void TestModel3D::OnImGuiRender()
	{
		ImGui::Begin("Translation");
		ImGui::Text(projection.c_str());
		ImGui::SliderFloat3("Translation", &m_Translation.x, -15.0f, 15.0f);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::End();
	}
}
