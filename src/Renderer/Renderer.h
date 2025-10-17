#pragma once
#include <glm/glm.hpp>

#include "Shader.h"


class IPrimitive;

class Renderer
{
public:
	Renderer(int width, int height)
	{
		Init(width, height);
	}

	void Init(int width, int height);

	void DrawPrimitive(const IPrimitive& mesh, const glm::mat4& transform, const glm::vec3& color) const;

private:
	Shader shader_;
	glm::mat4 projection_;
};