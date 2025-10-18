#pragma once
#include <array>

#include "glm/ext/scalar_constants.hpp"
#include "glm/trigonometric.hpp"


namespace PrimitiveVertex
{
	const std::array<float, 8> RectangleVertices =
	{
		0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
	};
	const std::array<unsigned int, 6> RectangleIndices =
	{
		0, 1, 2, 2, 3, 0
	};

	constexpr std::array<float, 6> TriangleVertices =
	{
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};


	constexpr int CIRCLE_SEGMENT_COUNT = 64;
	constexpr int CIRCLE_VERTEX_COUNT = CIRCLE_SEGMENT_COUNT + 2;
	constexpr int CIRCLE_ARRAY_SIZE = CIRCLE_VERTEX_COUNT * 2;

	inline std::array<float, CIRCLE_ARRAY_SIZE> GenerateCircleVertices()
	{
		std::array<float, CIRCLE_ARRAY_SIZE> vertices;
		constexpr float CIRCLE_RADIUS = 0.5f;

		vertices[0] = 0.0f;
		vertices[1] = 0.0f;

		for (int i = 0; i <= CIRCLE_SEGMENT_COUNT; ++i)
		{
			int baseIndex = 2 + i * 2;
			float angle = i * 2.0f * glm::pi<float>() / CIRCLE_SEGMENT_COUNT;
			vertices[baseIndex] = std::cos(angle) * CIRCLE_RADIUS;
			vertices[baseIndex + 1] = std::sin(angle) * CIRCLE_RADIUS;
		}

		return vertices;
	}

	inline static std::array<float, CIRCLE_ARRAY_SIZE> CircleVertices = GenerateCircleVertices();


};