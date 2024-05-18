#include "SimpleLighting.h"

#include "Application.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>

static float rotation = 1.0f;
static glm::mat4 model;
static glm::mat4 lightposition;
static int s_Projection = 1;
static bool pressed = false;
static bool pressed1 = false;

static std::string projection = "Perspective Projection";

static float s_FOV = 55.0f;

static glm::vec3 s_LightPosition{1.0f, 1.0f, 1.0f};
static glm::vec3 s_SpecularColor{1.0f, 1.0f, 1.0f};
static glm::vec3 s_AmbientLight{0.1f, 0.1f, 0.1f};
static float s_LightIntensity = 1.0f;
static float s_SpecularAlpha = 100.0f;
static glm::vec4 s_LightColor{1.0f, 1.0f, 1.0f, 1.0f};
static glm::vec4 s_ClearColor{ 0.25f, 0.2f, 0.25f, 1.0f };

namespace test {
	SimpleLighting::SimpleLighting()
	{
		m_Model = std::make_shared<Model>("res/model/CStellCube.obj");
		m_ModelMatrix = m_Model->GetModelMatrix();

		width = Application::Get().GetWindow().GetWidth();
		height = Application::Get().GetWindow().GetHeight();

		m_Proj = glm::perspective<double>(glm::radians(s_FOV), (float)(width) / height, 0.1f, 10000.0f);
		m_Camera.SetProjection(m_Proj);

		m_Texture = std::make_unique<Texture>("res/texture/CStell2.png");
	}

	SimpleLighting::~SimpleLighting()
	{
	}

	void SimpleLighting::OnUpdate(float deltaTime)
	{
		Input();
	}
	void SimpleLighting::OnRender()
	{
		GLCall(glClearColor(s_ClearColor.r, s_ClearColor.g, s_ClearColor.b, s_ClearColor.a));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_Camera.Input();

		m_Texture->Bind();
		m_Shader = m_Model->GetShader();
		m_Shader->Bind();

		m_Shader->SetUniform3f("u_LightPosition", s_LightPosition.x, s_LightPosition.y, s_LightPosition.z);
		m_Shader->SetUniform3f("u_AmbientLight", s_AmbientLight.x, s_AmbientLight.y, s_AmbientLight.z);
		m_Shader->SetUniform1f("u_LightIntensity", s_LightIntensity);
		m_Shader->SetUniform3f("u_SpecularColor", s_SpecularColor.x, s_SpecularColor.y, s_SpecularColor.z);
		m_Shader->SetUniform1f("u_SpecularAlpha", s_SpecularAlpha);
		m_Shader->SetUniform4f("u_LightColor", s_LightColor.x, s_LightColor.g, s_LightColor.b, s_LightColor.a);

		m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation) * glm::toMat4(glm::quat(glm::radians(m_Rotation))) *
			glm::scale(glm::mat4(1.0f), m_Scale);

		m_Model->UpdateModelMatrix(m_ModelMatrix);

		m_Model->DrawModel(m_Camera);

		if (s_Projection)
			m_Proj = glm::perspective<double>(glm::radians(s_FOV), (float)(width) / height, 0.1f, 10000.0f);
		else
			m_Proj = glm::ortho<double>(-32.0f, 32.0f, -18.0f, 18.0f, -1000.0f, 1000.0f);

		m_Camera.SetProjection(m_Proj);

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
				m_Proj = glm::ortho<double>(-32.0f, 32.0f, -18.0f, 18.0f, -1000.0f, 1000.0f);
				s_Projection = 0;
			}
			else
			{
				projection = "Perspective Projection";
				print(projection);
				m_Proj = glm::perspective<double>(glm::radians(s_FOV), (float)(width) / height, 0.1f, 10000.0f);
				s_Projection = 1;
			}
			m_Camera.SetProjection(m_Proj);
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
			m_Shader = m_Model->GetShader();
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
		ImGui::SliderFloat("Field of View", &s_FOV, 1.0f, 90.0f);

		ImGui::DragFloat3("Translation", glm::value_ptr(m_Translation));
		ImGui::DragFloat3("Rotation", glm::value_ptr(m_Rotation));
		ImGui::DragFloat3("Scale", glm::value_ptr(m_Scale), 1.0f);

		ImGui::SliderFloat3("Light Position", glm::value_ptr(s_LightPosition), -30.0f, 30.0f);
		ImGui::ColorEdit3("Ambient Light", glm::value_ptr(s_AmbientLight));
		ImGui::SliderFloat("Light Intensity", &s_LightIntensity, 0.0f, 10.0f);
		ImGui::ColorEdit4("Light Color", glm::value_ptr(s_LightColor));
		ImGui::ColorEdit3("Specular Color", glm::value_ptr(s_SpecularColor));
		ImGui::SliderFloat("Specular Alpha", &s_SpecularAlpha, 0.0f, 10000.0f);
		ImGui::ColorEdit4("Clear Color", glm::value_ptr(s_ClearColor));
		ImGui::End();
	}
}