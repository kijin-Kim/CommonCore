#pragma once
#include <memory>
#include <vector>

#include "EventBus.h"
#include "GLFW/glfw3.h"
#include "Layers/Layer.h"
#include "Renderer/Renderer.h"

struct GLFWwindow;

class Application
{
public:
	struct ApplicationSettings
	{
		int Width = 1920;
		int Height = 1080;
	};

public:
	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}

	void Initialize(const ApplicationSettings& settings);
	~Application();

	template <typename T, typename... Args>
	std::weak_ptr<T> AddLayer(Args&&... args)
	{
		std::shared_ptr<T> newLayer = std::make_shared<T>(std::forward<Args>(args)...);
		layers_.push_back(newLayer);
		return newLayer;
	}

	void Run();
	void OnFramebufferSizeChanged(GLFWwindow* window, int width, int height);
	void OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	const ApplicationSettings& GetSettings() const { return settings_; }

	glm::vec2 GetWorldCursorPosition() const;

private:
	Application() = default;
	void Update(float deltaTime);
	void Render();

private:
	ApplicationSettings settings_;
	std::vector<std::shared_ptr<ILayer>> layers_;
	GLFWwindow* window_;
	Renderer renderer_;
};