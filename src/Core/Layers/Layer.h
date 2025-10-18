#pragma once


class Renderer;

class ILayer
{
public:
	virtual ~ILayer() = default;

	virtual void OnInit()
	{
	}

	virtual void OnDestroy()
	{
	}

	virtual void OnUpdate(float deltaTime)
	{
	}

	virtual void OnRender(Renderer& renderer)
	{
	}
};