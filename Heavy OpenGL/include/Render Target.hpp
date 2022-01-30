#pragma once

#include "Vertex Array.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace hv {
	class RenderTarget;

	enum class Primitives
	{
		Triangles = 0,
		Lines,
		Points,
	};

	class Drawable {
	public:
		virtual void Draw(RenderTarget& target) = 0;
	};

	class RenderTarget {
	public:
		RenderTarget();
		~RenderTarget();

		void Draw(Drawable& drawable, const Shader* shader = nullptr);

		void Draw(const VertexArray& vertexArray, Primitives type, const Shader* shader = nullptr, const Texture* texture = nullptr, const IndexBuffer* indexBuffer = nullptr);

	private:
		static Shader* m_defaultShader;
		
		static uint32_t GetGLPrimitive(Primitives type);

	protected:
		static void Init();
	};
}