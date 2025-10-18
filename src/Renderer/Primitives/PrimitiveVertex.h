#pragma once


namespace PrimitiveVertex
{
	constexpr float RectangleVertices[] =
	{
		0.5f, -0.5f, 1.f, 1.f, 1.f,
		-0.5f, -0.5f, 1.f, 1.f, 1.f,
		-0.5f, 0.5f, 1.f, 1.f, 1.f,
		0.5f, 0.5f, 1.f, 1.f, 1.f,
	};
	const unsigned int RectangleIndices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	constexpr float TriangleVertices[] =
	{
		0.0f, 0.5f, 1.f, 1.f, 1.f,
		-0.5f, -0.5f, 1.f, 1.f, 1.f,
		0.5f, -0.5f, 1.f, 1.f, 1.f
	};

};