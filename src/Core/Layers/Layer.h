#pragma once


class EventBus;
class Renderer;

class ILayer
{
public:
	ILayer(EventBus& eventBus);
	virtual ~ILayer() = default;

	virtual void OnInit();

	virtual void OnDestroy();

	virtual void OnUpdate(float deltaTime);

	virtual void OnRender(Renderer& renderer);

protected:
	EventBus& eventBus_;
};