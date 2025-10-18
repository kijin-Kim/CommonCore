//
// Created by kijin on 2025-10-18.
//

#include "MainLayer.h"
#include "Renderer/Renderer.h"
#include "glm/ext/matrix_transform.hpp"

MainLayer::MainLayer()
	: circle_(64)
{
}

void MainLayer::OnInit()
{
	rect_.UploadData();
	tri_.UploadData();
	circle_.UploadData();
}

void MainLayer::OnUpdate(float deltaTime)
{
	transform_ = glm::translate(glm::mat4(1.0f), glm::vec3(400, 300, 0.0f));
	transform_ = glm::scale(transform_, glm::vec3(200.0f, 200.0f, 1.0f));
}

void MainLayer::OnRender(Renderer& renderer)
{
	renderer.DrawPrimitive(rect_, transform_, {1.0f, 1.0f, 0.0f});
	renderer.DrawPrimitive(tri_, transform_, {0.0f, 1.0f, 1.0f});
	renderer.DrawPrimitive(circle_, transform_, {1.0f, 0.0f, 1.0f});
}