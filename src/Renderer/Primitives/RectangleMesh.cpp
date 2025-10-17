#include "RectangleMesh.h"
#include <glad/glad.h>

RectangleMesh::RectangleMesh()
{
	constexpr float vertices[] = {
		0.5f, -0.5f, 1.f, 1.f, 1.f,
		-0.5f, -0.5f, 1.f, 1.f, 1.f,
		-0.5f, 0.5f, 1.f, 1.f, 1.f,
		0.5f, 0.5f, 1.f, 1.f, 1.f,
	};
	const unsigned int indices[] = {0, 1, 2, 2, 3, 0};

	unsigned int ebo;
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

	glBindVertexArray(0);
}

RectangleMesh::~RectangleMesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}