#include "RectangleMesh.h"
#include <glad/glad.h>

#include "PrimitiveVertex.h"

RectangleMesh::RectangleMesh(const glm::vec4& color, DrawMode drawMode)
	: IPrimitive(color, drawMode)
{
}

RectangleMesh::~RectangleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
}

void RectangleMesh::UploadData()
{
	unsigned int ebo;
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PrimitiveVertex::RectangleVertices), PrimitiveVertex::RectangleVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PrimitiveVertex::RectangleIndices), PrimitiveVertex::RectangleIndices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glBindVertexArray(0);
}

void RectangleMesh::Bind() const
{
	glBindVertexArray(vao_);
}

void RectangleMesh::Unbind() const
{
	glBindVertexArray(0);
}

void RectangleMesh::Draw() const
{
	glDrawElements(drawMode_ == DrawMode::Filled ? GL_TRIANGLES : GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr);
}