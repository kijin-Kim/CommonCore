#include "Shapes.h"

#include <glad/glad.h>

#include "Renderer.h"
#include "ShapeUtility.h"

#include "glm/ext/matrix_transform.hpp"


ConvexShape::ConvexShape(const std::vector<glm::vec2>& vertices)
{
	vertices_ = vertices;
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec2), vertices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
}

ConvexShape::~ConvexShape()
{
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void ConvexShape::Draw(Renderer& renderer, const glm::vec2& position, float rotation) const
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	renderer.Draw(vao_, GL_TRIANGLE_FAN, static_cast<GLsizei>(vertices_.size()), transform, color_);
}

CircleShape::CircleShape(float radius)
	: radius_(radius)
{
	vertices_ = ShapeUtility::UnitCircleVertices;
	for (glm::vec2& vertex : vertices_)
	{
		vertex *= radius_;
	}
}

void CircleShape::Draw(Renderer& renderer, const glm::vec2& position, float rotation) const
{
	renderer.DrawCircle(position, radius_, color_);
}

RectangleShape::RectangleShape(const glm::vec2& size)
	: size_(size)
{

	vertices_ = ShapeUtility::SquareVertices;
	for (glm::vec2& vertex : vertices_)
	{
		vertex *= size_;
	}
}

void RectangleShape::Draw(Renderer& renderer, const glm::vec2& position, float rotation) const
{
	renderer.DrawRectangle(position, rotation, size_, color_);
}