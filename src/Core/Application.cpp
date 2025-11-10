#include "Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <iostream>

#include "Renderer/Renderer.h"

#include "tracy/Tracy.hpp"
#include "tracy/TracyOpenGL.hpp"


void Application::Initialize(const ApplicationSettings& settings)
{
	settings_ = settings;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(settings_.Width, settings_.Height, "OpenGL + ImGui", nullptr, nullptr);
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

	glfwSetMouseButtonCallback(window_,
							   [](GLFWwindow* window, int button, int action, int mods)
							   {
								   Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
								   app->OnMouseButtonEvent(window, button, action, mods);
							   });
	glfwSetKeyCallback(window_,
					   [](GLFWwindow* window, int key, int scancode, int action, int mods)
					   {
						   Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
						   app->OnKeyEvent(window, key, scancode, action, mods);
					   });
}
Application::~Application()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Application::Run()
{
	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		layer->OnInit();
	}

	renderer_.Init(settings_.Width, settings_.Height);
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window_))
	{
		const float currentFrame = static_cast<float>(glfwGetTime());
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Update(deltaTime);
		Render();
		TracyGpuCollect;
		FrameMark;
	}

	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		layer->OnDestroy();
	}
}

void Application::OnFramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
	settings_.Width = width;
	settings_.Height = height;
	glViewport(0, 0, width, height);
}
void Application::OnMouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		if (layer->OnMouseButtonEvent(button, action, mods))
		{
			break;
		}
	}
}
void Application::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		if (layer->OnKeyEvent(key, scancode, action, mods))
		{
			break;
		}
	}
}
glm::vec2 Application::GetWorldCursorPosition() const
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);
	const Application::ApplicationSettings& settings = Application::GetInstance().GetSettings();
	int width = settings.Width;
	int height = settings.Height;
	glm::mat4 projection = renderer_.GetProjectionMatrix();
	mouseX = mouseX / width * 2.0f - 1.0f;
	mouseY = 1.0f - mouseY / height * 2.0f;

	glm::vec4 mousePosNDC = glm::vec4(static_cast<float>(mouseX), static_cast<float>(mouseY), 0.0f, 1.0f);
	glm::vec4 worldPos = glm::inverse(projection) * mousePosNDC;
	return glm::vec2(worldPos.x, worldPos.y);
}

void Application::Update(float deltaTime)
{
	glfwPollEvents();
	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		layer->OnUpdate(deltaTime);
	}
}

void Application::Render()
{
	TracyGpuZone("Application::Render");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (const std::shared_ptr<ILayer>& layer : layers_)
	{
		layer->OnRender(renderer_);
	}
	glfwSwapBuffers(window_);
}