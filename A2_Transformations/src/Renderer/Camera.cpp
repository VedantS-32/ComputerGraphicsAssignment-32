#include "Camera.h"

#include <cassert>
#include <limits>

void Camera::setOrthographicProjection(float left, float right, float top, float bottom, float near, float far)
{
	m_ProjectionMatrix = glm::mat4{ 1.0f };

	m_ProjectionMatrix[0][0] = 2.0f / (right - left);
	m_ProjectionMatrix[1][1] = 2.0f / (top - bottom);
	m_ProjectionMatrix[2][2] = 2.0f / (far - near);
	m_ProjectionMatrix[3][0] = -(right + left) / (right - left);
	m_ProjectionMatrix[3][1] = -(top + bottom) / (top - bottom);
	m_ProjectionMatrix[3][2] = -(far + near) / (far - near);
}

void Camera::setPerspectiveProjection(float fov, float aspect, float near, float far)
{
	assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
	const float tanHalfFovy = tan(glm::radians(fov / 2.f));

	m_ProjectionMatrix = glm::mat4{ 0.0f };
	m_ProjectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
	m_ProjectionMatrix[1][1] = 1.f / (tanHalfFovy);
	m_ProjectionMatrix[2][2] = far / (far - near);
	m_ProjectionMatrix[3][2] = -1.0f;
	m_ProjectionMatrix[2][3] = (far * near) / (far - near);
}
