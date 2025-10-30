#pragma once
#include <memory>
#include <vector>

#include "Layers/Layer.h"
#include "EventBus.h"

struct GLFWwindow;

class Application
{
public:
	explicit Application(int width, int height);
	~Application();
	template<typename T, typename... Args>
	void AddLayer(Args&&... args)
	{
		layers_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	void Run();
	void OnFramebufferSizeChanged(GLFWwindow* window, int width, int height);

private:
	void Update(float deltaTime);
	void Render(Renderer& renderer);

private:
	std::vector<std::unique_ptr<ILayer> > layers_;
	GLFWwindow* window_;
	int width_;
	int height_;
};