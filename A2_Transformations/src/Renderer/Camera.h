#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"

class Camera
{
public:

	void setOrthographicProjection(float left = -16.0f, float right = 16.0f, float top = 9.0f, float bottom = -9.0f,
		float near = -500.0f, float far = 500.f);
	void setPerspectiveProjection(float fov = glm::radians(30.0f), float aspect = (16.0f / 9.0f), float near = -500.0f, float far = 500.0f);
	void SetProjection(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
	const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
	inline const glm::vec3& GetPosition() const { return m_Position; }

	void Input();

	glm::mat4 m_ViewMatrix{ 1.0f };
	glm::vec3 m_Position{ 0.0f };
	glm::vec3 m_Orientation{ 0.0f, 1.0f, 0.0f };
private:
	glm::mat4 m_ProjectionMatrix{ 1.0f };

	glm::vec3 m_Up{ 0.0f, 0.0f, 1.0f };
	float m_Speed = 0.5f;
	float m_Sensitivity = 100.0f;
};