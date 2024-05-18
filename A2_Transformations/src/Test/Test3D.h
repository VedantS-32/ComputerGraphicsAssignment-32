#pragma once

#include "Test.h"
#include "Minimal.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/BufferLayout.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <memory>

namespace test {

	class Test3D : public Test
	{
	public:
		Test3D();
		~Test3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		glm::mat4 m_Proj;
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::vec3 m_Translation;
		glm::vec3 m_TranslationB;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		Camera m_Camera;
		std::unique_ptr <Model> m_Model;

		std::string m_Filepath;
	};
}