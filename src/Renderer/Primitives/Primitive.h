#pragma once
#include "glm/vec4.hpp"


class IPrimitive
{
public:
	explicit IPrimitive(const glm::vec4& color);
	virtual ~IPrimitive() = default;
	virtual void UploadData() = 0;
	virtual void Bind() const = 0;
	virtual void Draw() const = 0;
	virtual void Unbind() const = 0;
	glm::vec4 GetColor() const { return color_; }

protected:
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
	glm::vec4 color_;
};