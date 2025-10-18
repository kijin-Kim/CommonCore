#pragma once
#include <glm/glm.hpp>
#include <memory>

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

	void DrawPrimitive(const std::unique_ptr<IPrimitive>& mesh, const glm::mat4& transform) const;

private:
	Shader shader_;
	glm::mat4 projection_;
};