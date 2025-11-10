#pragma once
#include <glm/vec2.hpp>
#include <vector>

namespace ShapeUtility
{
	static std::vector<glm::vec2> CreateUnitCircleVertices()
	{
		static std::vector<glm::vec2> vertices;
		constexpr int SEGMENTS = 64;
		vertices.reserve(SEGMENTS);
		for (int i = 0; i < SEGMENTS; ++i)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(SEGMENTS);
			float x = cosf(theta);
			float y = sinf(theta);
			vertices.emplace_back(x, y);
		}
		return vertices;
	}

	inline static std::vector<glm::vec2> UnitCircleVertices = CreateUnitCircleVertices();
	inline static std::vector<glm::vec2> SquareVertices
		= {glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, 0.5f)};

	struct TextureVertex
	{
		glm::vec2 Position;
		glm::vec2 TexCoord;
	};

	inline static std::vector<TextureVertex> TexturedSquareVertices = {{glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},
																	   {glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 0.0f)},
																	   {glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f)},
																	   {glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 1.0f)}};

}; // namespace ShapeUtility