#include "Layer.h"

ILayer::ILayer(EventBus& eventBus)
	: eventBus_(eventBus)
{
}

void ILayer::OnInit()
{
}

void ILayer::OnDestroy()
{
}

void ILayer::OnUpdate(float deltaTime)
{
}

void ILayer::OnRender(Renderer& renderer)
{
}