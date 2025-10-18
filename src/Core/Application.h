#pragma once
#include <memory>
#include <vector>

#include "Layers/Layer.h"

struct GLFWwindow;

class Application
{
public:
	explicit Application(std::vector<std::unique_ptr<ILayer> > layers, int width, int height);
	~Application();
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