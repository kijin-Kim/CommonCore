#include "TriangleMesh.h"

#include <glad/glad.h>

TriangleMesh::TriangleMesh()
{
	float vertices[] = {
		0.0f, 0.5f, 1.f, 1.f, 1.f,
		-0.5f, -0.5f, 1.f, 1.f, 1.f,
		0.5f, -0.5f, 1.f, 1.f, 1.f
	};

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	glBindVertexArray(0);
}

TriangleMesh::~TriangleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
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