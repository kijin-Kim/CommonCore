#include "TriangleMesh.h"

#include <glad/glad.h>

#include "PrimitiveVertex.h"

TriangleMesh::TriangleMesh(const glm::vec4& color)
	: IPrimitive(color)
{
}

TriangleMesh::~TriangleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void TriangleMesh::UploadData()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PrimitiveVertex::TriangleVertices), PrimitiveVertex::TriangleVertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glBindVertexArray(0);
}

void TriangleMesh::Bind() const
{
	glBindVertexArray(vao_);
}

void TriangleMesh::Unbind() const
{
	glBindVertexArray(0);
}

void TriangleMesh::Draw() const
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}