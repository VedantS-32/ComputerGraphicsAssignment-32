#include "Camera.h"

#include "Input.h"
#include "Application.h"

#include <glfw/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <cassert>
#include <limits>

static std::pair<float, float> s_MousePos{0.0f, 0.0f};
static std::pair<float, float> s_MousePosCamera{0.0f, 0.0f};
static std::pair<float, float> s_PrevMousePos{ 0.0f, 0.0f };
static float s_ScrollDelta = 0.0;
static float s_PrevScrollDelta = 0.0;

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
	const float tanHalfFovy = tan(glm::radians(fov / 2.0f));

	m_ProjectionMatrix = glm::mat4{ 0.0f };
	m_ProjectionMatrix[0][0] = 1.f / (aspect * tanHalfFovy);
	m_ProjectionMatrix[1][1] = 1.f / (tanHalfFovy);
	m_ProjectionMatrix[2][2] = far / (far - near);
	m_ProjectionMatrix[2][3] = -1.0f;
	m_ProjectionMatrix[3][2] = (far * near) / (far - near);
}

void Camera::Input()
{
	s_PrevMousePos = s_MousePos;
	s_MousePos = Input::GetMousePosition();
	std::pair<float, float> mouseMoveDelta = { s_MousePos.first - s_PrevMousePos.first, s_MousePos.second - s_PrevMousePos.second };
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

	if (Input::IsKeyPressed(GLFW_KEY_W))
		m_Position += m_Speed * m_Orientation;
	if (Input::IsKeyPressed(GLFW_KEY_S))
		m_Position -= m_Speed *  m_Orientation;
	if (Input::IsKeyPressed(GLFW_KEY_A))
		m_Position += m_Speed * glm::cross(m_Up, m_Orientation);
	if (Input::IsKeyPressed(GLFW_KEY_D))
		m_Position -= m_Speed * glm::cross(m_Up, m_Orientation);
	if (Input::IsKeyPressed(GLFW_KEY_Q))
		m_Position -= m_Speed * m_Up;
	if (Input::IsKeyPressed(GLFW_KEY_E))
		m_Position += m_Speed * m_Up;
	if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		uint32_t width = Application::Get().GetWindow().GetWidth();
		uint32_t height = Application::Get().GetWindow().GetHeight();

		float rotX = m_Sensitivity * (float)(mouseMoveDelta.first) / width;
		float rotY = m_Sensitivity * (float)(mouseMoveDelta.second) / height;

		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotX), m_Up);
		m_Orientation = glm::rotate(m_Orientation, glm::radians(rotY), glm::cross(m_Up, m_Orientation));

		s_PrevScrollDelta = s_ScrollDelta;
		s_ScrollDelta = Input::GetMouseScrollOffset().second;
		float scroll = s_ScrollDelta - s_PrevScrollDelta;
		if (scroll)
		{
			m_Speed += ((scroll) / 20);
			m_Speed = glm::abs(m_Speed);
		}
	}
	else if (Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_RIGHT))
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}
