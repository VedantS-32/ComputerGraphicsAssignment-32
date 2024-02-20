#pragma once

#include "Test.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {

	class SimpleLighting : public Test
	{
	public:
		SimpleLighting();
		virtual ~SimpleLighting();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void Input() override;
		virtual void OnImGuiRender() override;

		glm::mat4 m_Proj;
		glm::vec3 m_Translation;
		Camera m_Camera;
		//glm::vec3 m_TranslationB;

	private:
		float m_ClearColor[4];

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr <Model> m_Model;

		std::string m_Filepath;
	};
}