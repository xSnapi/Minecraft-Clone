#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Window.hpp"

namespace hv {
	class Camera {
	public:
		Camera();
		~Camera();

		void Create(const Window& window, uint32_t width, uint32_t height, float near = 0.1f, float far = 100.0f);

		glm::mat4 Update();

		void BasicMove(float velocity);

		void Move(glm::vec3 offset);
		void SetPosition(glm::vec3 position);

		glm::vec3 GetUp() const;
		glm::vec3 GetFront() const;
		glm::mat4 GetProjection() const;

		//TODO: Add get position 

	private:
		const Window* m_window = nullptr;

		float m_fov = 80.0f;

		float m_yaw   = -90.0f;
		float m_pitch = -90.0f;

		float m_sensitivity = 0.1f;

		glm::vec2 m_lastMousePos;

		glm::vec3 m_position;

		glm::vec3 m_up;
		glm::vec3 m_front;

		glm::mat4 m_view;
		glm::mat4 m_projection;

		void LookAtMouse();
	};
}