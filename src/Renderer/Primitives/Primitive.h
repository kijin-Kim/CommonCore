#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

#include <vector>

enum class DrawMode
{
	Lines,
	Filled
};


class IPrimitive
{
public:
	explicit IPrimitive(const glm::vec4& color, DrawMode drawMode);
	virtual ~IPrimitive() = default;
	virtual void UploadData() = 0;
	virtual void Bind() const = 0;
	virtual void Draw() const = 0;
	virtual void Unbind() const = 0;

	void SetColor(const glm::vec4& color) { color_ = color; }
	glm::vec4 GetColor() const { return color_; }


protected:
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	glm::vec4 color_;
	DrawMode drawMode_ = DrawMode::Filled;
	std::vector<glm::vec2> vertices_;
};