#pragma once

#include <glad/glad.h>
#include "Shader.h"

class Renderer
{
public:
	Renderer(int width, int height)
	{
		Init(width, height);
	}

	~Renderer();
	void Init(int width, int height);
	void Draw(unsigned int vao, GLenum mode, GLsizei vertexCount, const glm::mat4& transform, const glm::vec4& color);
	void DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color);
	void DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);


	void BeginScene();
	void EndScene();

private:
	Shader shader_;
	glm::mat4 projection_;

	unsigned int circleVao_ = 0;
	unsigned int circleVbo_ = 0;

	unsigned int squareVao_ = 0;
	unsigned int squareVbo_ = 0;
	unsigned int squareEbo_ = 0;


};