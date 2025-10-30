#pragma once
#include <vector>

#include "Core/EventBus.h"

class EventBus;
class Renderer;

class ILayer
{
public:
	ILayer();
	virtual ~ILayer() = default;

	virtual void OnInit();
	virtual void OnDestroy();

	virtual void OnUpdate(float deltaTime);

	virtual void OnRender(Renderer& renderer);
};