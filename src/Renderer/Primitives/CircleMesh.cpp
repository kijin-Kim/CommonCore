#include "CircleMesh.h"
#include <cmath>
#include <vector>

#include <glad/glad.h>

#include "PrimitiveVertex.h"


CircleMesh::CircleMesh(const glm::vec4& color)
	: IPrimitive(color)
{
}

CircleMesh::~CircleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void CircleMesh::UploadData()
{

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, PrimitiveVertex::CircleVertices.size() * sizeof(float), PrimitiveVertex::CircleVertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glBindVertexArray(0);
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, PrimitiveVertex::CIRCLE_VERTEX_COUNT);
}