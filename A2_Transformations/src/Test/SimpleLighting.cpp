#include "SimpleLighting.h"

#include "Input.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>

static float rotation = 1.0f;
static glm::mat4 model;
static int s_Projection = 1;
static bool pressed = false;
static bool pressed1 = false;

static std::string projection = "Perspective Projection";

static float s_LightPosition[3] = {1.0f, 1.0f, 1.0f};
static float s_SpecularColor[3] = {1.0f, 1.0f, 1.0f};
static float s_AmbientLight[3] = {0.1f, 0.1f, 0.1f};
static float s_LightIntensity = 1.0f;
static float s_SpecularAlpha = 100.0f;
static float s_LightColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

namespace test {
	SimpleLighting::SimpleLighting()
		: m_Translation(0.0f, 25.0f, -5.0f),
		m_Filepath("res/mesh/Apple.fbx"),
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


		m_Shader = std::make_unique<Shader>("shader/SimpleLighting.vert", "shader/SimpleLighting.frag");
		m_Texture = std::make_unique<Texture>("res/texture/CStell2.png");

		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	SimpleLighting::~SimpleLighting()
	{
	}

	void SimpleLighting::OnUpdate(float deltaTime)
	{
		Input();

		if (rotation >= 360.f)
			rotation = 0.0f;
		rotation += 0.1f;
	}
	void SimpleLighting::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;
		model = glm::translate(glm::mat4(1.0f), m_Translation);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Camera.Input();
		glm::vec3 cameraPosition = m_Camera.GetPosition() + m_Translation;
		glm::mat4 view = m_Camera.m_ViewMatrix;
		glm::mat4 modelView = view * model;
		glm::mat4 mvp = m_Proj * view * model;
		m_Shader->SetUniformMat4f("u_ModelView", modelView);
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform3f("u_LightPosition", s_LightPosition[0], s_LightPosition[1], s_LightPosition[2]);
		m_Shader->SetUniform3f("u_AmbientLight", s_AmbientLight[0], s_AmbientLight[1], s_AmbientLight[2]);
		m_Shader->SetUniform1f("u_LightIntensity", s_LightIntensity);
		m_Shader->SetUniform3f("u_CameraPosition", cameraPosition[0], cameraPosition[1], cameraPosition[2]);
		m_Shader->SetUniform3f("u_SpecularColor", s_SpecularColor[0], s_SpecularColor[1], s_SpecularColor[2]);
		m_Shader->SetUniform1f("u_SpecularAlpha", s_SpecularAlpha);
		m_Shader->SetUniform4f("u_LightColor", s_LightColor[0], s_LightColor[1], s_LightColor[2], s_LightColor[3]);

		renderer.Draw(*m_VertexArray, *m_VertexBuffer, *m_Shader, m_IndexBuffer->GetCount() * sizeof(unsigned int));
	}

	void SimpleLighting::Input()
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

	void SimpleLighting::OnImGuiRender()
	{
		ImGui::Begin("Simple Lighting");
		ImGui::Text(projection.c_str());
		ImGui::SliderFloat3("Translation", &m_Translation.x, -30.0f, 30.0f);
		ImGui::SliderFloat3("Light Position", s_LightPosition, -10.0f, 10.0f);
		ImGui::ColorEdit3("Ambient Light", s_AmbientLight);
		ImGui::SliderFloat("Light Intensity", &s_LightIntensity, 0.0f, 10.0f);
		ImGui::ColorEdit4("Light Color", s_LightColor);
		ImGui::ColorEdit3("Specular Color", s_SpecularColor);
		ImGui::SliderFloat("Specular Alpha", &s_SpecularAlpha, 0.0f, 10000.0f);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::End();
	}
}
