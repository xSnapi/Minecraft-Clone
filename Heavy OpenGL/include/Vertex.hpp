#pragma once

#include "GLM/vec2.hpp"

namespace hv {
	struct Vertex2D
	{
		glm::vec2 Position = glm::vec2(0.0f);
		glm::vec2 TexCoord = glm::vec2(0.0f);
		glm::vec4 Color    = glm::vec4(1.0f);

		Vertex2D(glm::vec2 position)
			: Position(position)
		{

		}

		Vertex2D(glm::vec2 position, glm::vec2 texCoord)
			: Position(position)
			, TexCoord(texCoord)
		{

		}

		Vertex2D(glm::vec2 position, glm::vec4 color)
			: Position(position)
			, Color(color)
		{

		}

		Vertex2D(glm::vec2 position, glm::vec2 texCoord, glm::vec4 color)
			: Position(position)
			, TexCoord(texCoord)
			, Color(color)
		{

		}
	};
}

namespace hv {
	struct Vertex3D
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 TexCoord = glm::vec2(0.0f);
		glm::vec4 Color    = glm::vec4(1.0f);
	
		Vertex3D(glm::vec3 position)
			: Position(position)
		{
	
		}
	
		Vertex3D(glm::vec3 position, glm::vec2 texCoord)
			: Position(position)
			, TexCoord(texCoord)
		{
	
		}
	
		Vertex3D(glm::vec3 position, glm::vec4 color)
			: Position(position)
			, Color(color)
		{
	
		}
	
		Vertex3D(glm::vec3 position, glm::vec2 texCoord, glm::vec4 color)
			: Position(position)
			, TexCoord(texCoord)
			, Color(color)
		{
	
		}
	};
}