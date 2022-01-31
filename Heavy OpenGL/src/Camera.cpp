#include <hvpch.h>
#include "Camera.hpp"

#include "Mouse.hpp"
#include "Keyboard.hpp"

#include "Heavy Times.hpp"

using namespace hv;

Camera::Camera()
	: m_lastMousePos(0.0f, 0.0f)
	, m_position	(0.0f, 0.0f,  0.0f)
	, m_up			(0.0f, 1.0f,  0.0f)
	, m_front		(0.0f, 0.0f, -1.0f)
	, m_projection  (1.0f)
	, m_view		(1.0f)
{
	
}

Camera::~Camera() {

}

void Camera::Create(const Window& window, uint32_t width, uint32_t height, float near, float far) {
	m_window = &window;

	m_projection = glm::perspective
	(
		glm::radians(m_fov), 
		(float)width / (float)height,
		near,
		far
	);
}

glm::mat4 Camera::Update() {
	LookAtMouse();

	m_view = glm::lookAt(m_position, m_position + m_front, m_up);

	return m_projection * m_view;
}

void Camera::BasicMove(float velocity) {
	if (hv::Keyboard::IsKeyPressed(hv::Key::D))
		m_position += glm::normalize(glm::cross(m_front, m_up)) * velocity * dt;
	if (hv::Keyboard::IsKeyPressed(hv::Key::A))
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * velocity * dt;

	if (hv::Keyboard::IsKeyPressed(hv::Key::W))
		m_position += velocity * dt * m_front;
	if (hv::Keyboard::IsKeyPressed(hv::Key::S))
		m_position -= velocity * dt * m_front;

	if (hv::Keyboard::IsKeyPressed(hv::Key::Space))
		m_position += glm::vec3(0.0f, velocity * dt, 0.0f);
	if (hv::Keyboard::IsKeyPressed(hv::Key::LShift))
		m_position -= glm::vec3(0.0f, velocity * dt, 0.0f);

}

void Camera::Move(glm::vec3 offset) {
	m_position += offset;
}

void Camera::SetPosition(glm::vec3 position) {
	m_position = position;
}

glm::vec3 Camera::GetUp() const {
	return m_up;
}

glm::vec3 Camera::GetFront() const {
	return m_front;
}

glm::mat4 Camera::GetProjection() const {
	return m_projection * m_view;
}

void Camera::LookAtMouse() {
	glm::vec2 mousePos(Mouse::GetPosition(*m_window));

	glm::vec2 offset(mousePos.x - m_lastMousePos.x, m_lastMousePos.y - mousePos.y);

	m_lastMousePos = mousePos;

	offset *= m_sensitivity;

	m_yaw   += offset.x;
	m_pitch += offset.y;

	m_pitch = m_pitch > 89.9f ? 89.9f : m_pitch < -89.9f ? -89.9f : m_pitch;

	glm::vec3 cameraFront
	(
		cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch)),
		sinf(glm::radians(m_pitch)),
		sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch))
	);

	m_front = glm::normalize(cameraFront);
}
