#pragma once

#include "Test.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/BufferLayout.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>

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
		Camera m_Camera;

	private:
		uint32_t width;
		uint32_t height;

		std::shared_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::shared_ptr <Model> m_Model;

		glm::mat4 m_ModelMatrix{ 1.0f };
		glm::vec3 m_Translation{ 0.0f };
		glm::vec3 m_Rotation{ 0.0f };
		glm::vec3 m_Scale{ 1.0f };
	};
}