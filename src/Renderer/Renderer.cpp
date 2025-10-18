#include "Renderer.h"

#include "Primitives/Primitive.h"

#include "glm/ext/matrix_clip_space.hpp"

void Renderer::Init(int width, int height)
{
	shader_ = Shader("shaders/basic.vert", "shaders/basic.frag");
	projection_ = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
}

void Renderer::DrawPrimitive(const std::unique_ptr<IPrimitive>& mesh, const glm::mat4& transform) const
{
	shader_.Use();
	shader_.SetMat4("u_MVP", projection_ * transform);
	shader_.SetVec4("u_Color", mesh->GetColor());
	mesh->Bind();
	mesh->Draw();
	mesh->Unbind();
}