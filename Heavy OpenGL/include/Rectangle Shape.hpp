#pragma once

#include "Shape.hpp"

namespace hv {
	class RectangleShape : public Shape {
	public:
		RectangleShape();
		~RectangleShape();

		void SetSize(glm::vec2 size);

		glm::vec2 GetSize() const;

	private:

		glm::vec2 m_size;

		virtual void RecreateVertices();
	};
}