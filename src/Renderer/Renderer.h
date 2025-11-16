#pragma once

#include "Framebuffer.h"
#include "Shader.h"

#include "ImageTexture.h"
#include <glad/glad.h>
#include <memory>

class Renderer
{
public:
	struct TextureRegion
	{
		glm::vec2 UVStart;
		glm::vec2 UVEnd;
	};

public:
	~Renderer();
	void Init(int width, int height);
	void Draw(unsigned int vao, GLenum mode, GLsizei vertexCount, const glm::mat4& transform, const glm::vec4& color);
	void DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color);
	void DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color,
					   bool bOutline = false);
	void DrawTexturedRectangle(const glm::vec2& position, float rotation, const glm::vec2& size, std::shared_ptr<ImageTexture> texture,
							   const TextureRegion& region = {{0.0f, 0.0f}, {1.0f, 1.0f}});
	void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color, float thickness = 1.0f);

	void BeginScene(const std::shared_ptr<Framebuffer>& framebuffer = nullptr);
	void Clear(const glm::vec4& clearColor);
	void EndScene();

	glm::mat4 GetProjectionMatrix() const { return projection_; }

private:
	Shader basicShader_;
	Shader textureShader_;
	glm::mat4 projection_;

	unsigned int circleVao_ = 0;
	unsigned int circleVbo_ = 0;

	unsigned int squareVao_ = 0;
	unsigned int squareVbo_ = 0;
	unsigned int squareEbo_ = 0;

	unsigned int texturedSquareVao_ = 0;
	unsigned int texturedSquareVbo_ = 0;
	unsigned int texturedSquareEbo_ = 0;

	int screenWidth_ = 0;
	int screenHeight_ = 0;
};