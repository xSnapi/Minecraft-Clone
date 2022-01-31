#pragma once

#include "Shape.hpp"

namespace hv {
	class CircleShape : public Shape {
	public:
		CircleShape();
		~CircleShape();

		void SetRadius(float radius);

		float GetRadius() const;
	private:
		float m_radius;

		virtual void RecreateVertices();
	};
}