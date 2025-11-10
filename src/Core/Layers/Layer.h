#pragma once


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
	virtual bool OnMouseButtonEvent(int button, int action, int mods) { return false; }
	virtual bool OnKeyEvent(int key, int scancode, int action, int mods) { return false; }
};