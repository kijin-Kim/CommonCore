#include "CircleMesh.h"
#include <cmath>
#include <vector>

#include <glad/glad.h>

#include "glm/ext/scalar_constants.hpp"

CircleMesh::CircleMesh(int segments)
	: segmentCount_(segments)
{
	std::vector<float> vertices;
	vertices.reserve((segments + 2) * 5);

	// 중심점
	vertices.insert(vertices.end(), {0.f, 0.f, 1.f, 1.f, 1.f});

	for (int i = 0; i <= segments; ++i)
	{
		float angle = i * 2.0f * glm::pi<float>() / segments;
		vertices.push_back(std::cos(angle) * 0.5f);
		vertices.push_back(std::sin(angle) * 0.5f);
		vertices.push_back(1.f);
		vertices.push_back(1.f);
		vertices.push_back(1.f);
	}

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	glBindVertexArray(0);
}

CircleMesh::~CircleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void CircleMesh::Bind() const
{
	glBindVertexArray(vao_);
}

void CircleMesh::Unbind() const
{
	glBindVertexArray(0);
}

void CircleMesh::Draw() const
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, segmentCount_ + 2);
}