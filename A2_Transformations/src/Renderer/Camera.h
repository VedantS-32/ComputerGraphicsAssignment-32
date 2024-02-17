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
	const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }

private:
	glm::mat4 m_ProjectionMatrix{ 1.0f };
	glm::mat4 m_ViewMatrix = glm::mat4(1.0);
};