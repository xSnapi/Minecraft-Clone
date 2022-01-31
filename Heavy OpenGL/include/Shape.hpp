#pragma once

#include <GLM/glm.hpp>

#include "Vertex Array.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "Render Target.hpp"

/*
	TexCoords in vec4
	x = X start
	y = Y start

	z = X size
	w = Y size
*/

namespace hv {
	class Shape : public Drawable {
	public:
		static void Init(glm::mat4 projection);

		Shape();
		virtual ~Shape();

		void SetRotation(float rotation);
		void SetPosition(glm::vec2 position);
		void SetScale(glm::vec2 scale);
		void SetOrigin(glm::vec2 origin);
		void SetColor(glm::vec4 color);
		void SetTexCoords(glm::vec4 texCoords);

		glm::vec4 GetTexCoords() const;
		glm::vec4 GetColor() const;
		glm::vec2 GetOrigin() const;
		glm::vec2 GetScale() const;
		glm::vec2 GetPosition() const;
		float GetRotation() const;

		void SetTexture(Texture& tx);

	protected:
		glm::vec2 m_position;
		glm::vec2 m_origin;
		glm::vec2 m_scale;

		glm::vec4 m_texCoords;

		float	  m_rotation;

		glm::vec4 m_color;

		VertexArray  m_vertexArray;
		VertexBuffer m_vertexBuffer;

		IndexBuffer  m_indexBuffer;

		VertexBufferLayout m_layout;

		Texture* m_texture = nullptr;

		static Shader* s_defaultShader;
		static Shader* s_circleShader;

		static void LoadShaders();

		virtual void RecreateVertices() = 0;

		virtual void Draw(RenderTarget& target);
	};
}