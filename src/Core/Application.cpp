#include "Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <iostream>

#include "Renderer/Renderer.h"

#include "tracy/Tracy.hpp"
#include "tracy/TracyOpenGL.hpp"

Application::Application(int width, int height)
	: window_(nullptr)
	, width_(width)
	, height_(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width_, height_, "OpenGL + ImGui", nullptr, nullptr);
	if (!window_)
	{
		return;
	}

	glfwSetWindowUserPointer(window_, this);
	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_,
								   [](GLFWwindow* window, int width, int height)
								   {
									   Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
									   app->OnFramebufferSizeChanged(window, width, height);
								   });
	glfwSwapInterval(0); // VSync Off

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "GLAD init failed\n";
		return;
	}
	TracyGpuContext;
}

Application::~Application()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Application::Run()
{
	for (const std::unique_ptr<ILayer>& layer : layers_)
	{
		layer->OnInit();
	}

	Renderer renderer(width_, height_);
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window_))
	{
		const float currentFrame = static_cast<float>(glfwGetTime());
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Update(deltaTime);
		Render(renderer);
		TracyGpuCollect;
		FrameMark;
	}

	for (const std::unique_ptr<ILayer>& layer : layers_)
	{
		layer->OnDestroy();
	}
}

void Application::OnFramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::Update(float deltaTime)
{
	glfwPollEvents();
	for (const std::unique_ptr<ILayer>& layer : layers_)
	{
		layer->OnUpdate(deltaTime);
	}
}

void Application::Render(Renderer& renderer)
{
	TracyGpuZone("Application::Render");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (const std::unique_ptr<ILayer>& layer : layers_)
	{
		layer->OnRender(renderer);
	}
	glfwSwapBuffers(window_);
}