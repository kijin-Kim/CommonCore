#pragma once
#include "glm/vec2.hpp"

#include <vector>

#include "glm/fwd.hpp"
#include "glm/vec4.hpp"

class Renderer;

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void Draw(Renderer& renderer, const glm::vec2& position, float rotation) const = 0;
	const std::vector<glm::vec2>& GetVertices() const { return vertices_; }
	void SetColor(const glm::vec4& color) { color_ = color; }

protected:
	std::vector<glm::vec2> vertices_;
	glm::vec4 color_ = glm::vec4(1.0f);
};

class ConvexShape : public Shape
{
public:
	explicit ConvexShape(const std::vector<glm::vec2>& vertices);
	virtual ~ConvexShape();
	virtual void Draw(Renderer& renderer, const glm::vec2& position, float rotation) const override;

private:
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
};

class CircleShape : public Shape
{
public:
	explicit CircleShape(float radius);
	virtual void Draw(Renderer& renderer, const glm::vec2& position, float rotation) const override;

private:
	float radius_;
};

class RectangleShape : public Shape
{
public:
	explicit RectangleShape(const glm::vec2& size);
	virtual void Draw(Renderer& renderer, const glm::vec2& position, float rotation) const override;

private:
	glm::vec2 size_;
};