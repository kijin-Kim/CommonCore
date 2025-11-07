#include "Renderer.h"

#include "ShapeUtility.h"
#include "Shapes.h"
#include "imgui_impl_opengl3_loader.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Renderer::~Renderer()
{
	glDeleteBuffers(1, &circleVbo_);
	glDeleteVertexArrays(1, &circleVao_);

	glDeleteBuffers(1, &squareEbo_);
	glDeleteBuffers(1, &squareVbo_);
	glDeleteVertexArrays(1, &squareVao_);
}

void Renderer::Init(int width, int height)
{
	shader_ = Shader("shaders/basic.vert", "shaders/basic.frag");
	projection_ = glm::ortho(-static_cast<float>(width) / 2.0f, static_cast<float>(width) / 2.0f,
							 -static_cast<float>(height) / 2.0f, static_cast<float>(height) / 2.0f, -1.0f, 1.0f);

	// circle
	glGenVertexArrays(1, &circleVao_);
	glGenBuffers(1, &circleVbo_);
	glBindVertexArray(circleVao_);
	glBindBuffer(GL_ARRAY_BUFFER, circleVbo_);
	glBufferData(GL_ARRAY_BUFFER, ShapeUtility::UnitCircleVertices.size() * sizeof(glm::vec2),
				 ShapeUtility::UnitCircleVertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

	// square
	glGenVertexArrays(1, &squareVao_);
	glGenBuffers(1, &squareVbo_);
	glGenBuffers(1, &squareEbo_);
	glBindVertexArray(squareVao_);
	glBindBuffer(GL_ARRAY_BUFFER, squareVbo_);

	glBufferData(GL_ARRAY_BUFFER, ShapeUtility::SquareVertices.size() * sizeof(glm::vec2),
				 ShapeUtility::SquareVertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	unsigned int squareIndices[] = {0, 1, 2, 2, 3, 0};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareEbo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
}

void Renderer::Draw(unsigned int vao, GLenum mode, GLsizei vertexCount, const glm::mat4& transform,
					const glm::vec4& color)
{
	// TODO: OpenGL 상태 변경 최적화. 현재는 그냥 바로 그리기 명령
	shader_.SetMat4("u_Model", transform);
	shader_.SetVec4("u_Color", color);
	glBindVertexArray(vao);
	glDrawArrays(mode, 0, vertexCount);
}

void Renderer::DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::scale(transform, glm::vec3(radius, radius, 1.0f));
	Draw(circleVao_, GL_TRIANGLE_FAN, static_cast<GLsizei>(ShapeUtility::UnitCircleVertices.size()), transform, color);
}

void Renderer::DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color,
							 bool bOutline)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));
	shader_.SetMat4("u_Model", transform);
	shader_.SetVec4("u_Color", color);
	glBindVertexArray(squareVao_);
	glDrawElements(bOutline ? GL_LINE_LOOP : GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Renderer::BeginScene()
{
	shader_.Use();
	shader_.SetMat4("u_ViewProjection", projection_);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Renderer::EndScene() {}