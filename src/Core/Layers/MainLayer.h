#pragma once
#include "Layer.h"

#include "Renderer/Primitives/CircleMesh.h"
#include "Renderer/Primitives/RectangleMesh.h"
#include "Renderer/Primitives/TriangleMesh.h"
#include <glm/glm.hpp>


class MainLayer : public ILayer
{
public:
	MainLayer();
	virtual void OnInit() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender(Renderer& renderer) override;

private:
	RectangleMesh rect_;
	TriangleMesh tri_;
	CircleMesh circle_;
	glm::mat4 transform_;
};