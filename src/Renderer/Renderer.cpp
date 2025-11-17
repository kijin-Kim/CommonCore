#include "Renderer.h"

#include "Core/Application.h"

#include "ShapeUtility.h"
#include "Shapes.h"

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
	std::filesystem::path shaderPath = "shaders";

	basicShader_ = Shader(shaderPath / "basic.vert", shaderPath / "basic.frag");
	textureShader_ = Shader(shaderPath / "texture.vert", shaderPath / "texture.frag");
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

	// textured square
	glGenVertexArrays(1, &texturedSquareVao_);
	glGenBuffers(1, &texturedSquareVbo_);
	glGenBuffers(1, &texturedSquareEbo_);
	glBindVertexArray(texturedSquareVao_);
	glBindBuffer(GL_ARRAY_BUFFER, texturedSquareVbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ShapeUtility::TextureVertex) * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeUtility::TextureVertex),
						  reinterpret_cast<void*>(offsetof(ShapeUtility::TextureVertex, Position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeUtility::TextureVertex),
						  reinterpret_cast<void*>(offsetof(ShapeUtility::TextureVertex, TexCoord)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texturedSquareEbo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
}

void Renderer::Draw(unsigned int vao, GLenum mode, GLsizei vertexCount, const glm::mat4& transform,
					const glm::vec4& color)
{
	basicShader_.Use();
	projection_
		= glm::ortho(-static_cast<float>(screenWidth_) / 2.0f, static_cast<float>(screenWidth_) / 2.0f,
					 -static_cast<float>(screenHeight_) / 2.0f, static_cast<float>(screenHeight_) / 2.0f, -1.0f, 1.0f);
	basicShader_.SetMat4("u_ViewProjection", projection_);
	basicShader_.SetMat4("u_Model", transform);
	basicShader_.SetVec4("u_Color", color);
	glBindVertexArray(vao);
	glDrawArrays(mode, 0, vertexCount);
}

void Renderer::DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color)
{
	basicShader_.Use();
	projection_
		= glm::ortho(-static_cast<float>(screenWidth_) / 2.0f, static_cast<float>(screenWidth_) / 2.0f,
					 -static_cast<float>(screenHeight_) / 2.0f, static_cast<float>(screenHeight_) / 2.0f, -1.0f, 1.0f);
	basicShader_.SetMat4("u_ViewProjection", projection_);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::scale(transform, glm::vec3(radius, radius, 1.0f));
	Draw(circleVao_, GL_TRIANGLE_FAN, static_cast<GLsizei>(ShapeUtility::UnitCircleVertices.size()), transform, color);
}

void Renderer::DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color,
							 bool bOutline)
{
	basicShader_.Use();
	projection_
		= glm::ortho(-static_cast<float>(screenWidth_) / 2.0f, static_cast<float>(screenWidth_) / 2.0f,
					 -static_cast<float>(screenHeight_) / 2.0f, static_cast<float>(screenHeight_) / 2.0f, -1.0f, 1.0f);
	basicShader_.SetMat4("u_ViewProjection", projection_);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));
	basicShader_.SetMat4("u_Model", transform);
	basicShader_.SetVec4("u_Color", color);
	basicShader_.SetBool("u_UseTexture", false);
	glBindVertexArray(squareVao_);
	glDrawElements(bOutline ? GL_LINE_LOOP : GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Renderer::DrawTexturedRectangle(const glm::vec2& position, float rotation, const glm::vec2& size,
									 std::shared_ptr<ImageTexture> texture, const TextureRegion& region)
{
	textureShader_.Use();
	const Application::Settings& settings = Application::GetInstance().GetSettings();
	projection_
		= glm::ortho(-static_cast<float>(screenWidth_) / 2.0f, static_cast<float>(screenWidth_) / 2.0f,
					 -static_cast<float>(screenHeight_) / 2.0f, static_cast<float>(screenHeight_) / 2.0f, -1.0f, 1.0f);
	textureShader_.SetMat4("u_ViewProjection", projection_);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(position, 0.0f));
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	textureShader_.SetMat4("u_Model", transform);
	textureShader_.SetInt("u_Texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());

	// Update UVs
	ShapeUtility::TextureVertex vertices[4] = {
		{{-0.5f, -0.5f}, {region.UVStart.x, region.UVEnd.y}},
		{{0.5f, -0.5f}, {region.UVEnd.x, region.UVEnd.y}},
		{{0.5f, 0.5f}, {region.UVEnd.x, region.UVStart.y}},
		{{-0.5f, 0.5f}, {region.UVStart.x, region.UVStart.y}},
	};
	glBindBuffer(GL_ARRAY_BUFFER, texturedSquareVbo_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindVertexArray(texturedSquareVao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color, float thickness)
{
	basicShader_.Use();
	projection_
		= glm::ortho(-static_cast<float>(screenWidth_) / 2.0f, static_cast<float>(screenWidth_) / 2.0f,
					 -static_cast<float>(screenHeight_) / 2.0f, static_cast<float>(screenHeight_) / 2.0f, -1.0f, 1.0f);

	basicShader_.SetMat4("u_ViewProjection", projection_);

	glm::vec2 direction = end - start;
	float length = glm::length(direction);
	float angle = atan2(direction.y, direction.x);

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 midPoint = start + direction * 0.5f;
	transform = glm::translate(transform, glm::vec3(midPoint, 0.0f));
	transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(length, thickness, 1.0f));

	basicShader_.SetMat4("u_Model", transform);
	basicShader_.SetVec4("u_Color", color);
	glBindVertexArray(squareVao_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::BeginScene(const std::shared_ptr<Framebuffer>& framebuffer)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (framebuffer)
	{
		screenWidth_ = framebuffer->GetWidth();
		screenHeight_ = framebuffer->GetHeight();
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetFboId());
	}
	else
	{
		const Application::Settings& settings = Application::GetInstance().GetSettings();
		screenWidth_ = settings.Width;
		screenHeight_ = settings.Height;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
void Renderer::Clear(const glm::vec4& clearColor)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
