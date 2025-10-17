#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <iostream>

#include "Renderer/Renderer.h"
#include "Renderer/Primitives/CircleMesh.h"
#include "Renderer/Primitives/RectangleMesh.h"
#include "Renderer/Primitives/TriangleMesh.h"

#include "glm/gtc/matrix_transform.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	constexpr int width = 800;
	constexpr int height = 600;
	// --- GLFW init ---
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL + ImGui", nullptr, nullptr);
	if (!window)
		return -1;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // VSync

	// --- GLAD init ---
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "GLAD init failed\n";
		return -1;
	}

	// --- ImGui init ---
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	Renderer renderer(800, 600);
	RectangleMesh rect;
	TriangleMesh tri;
	CircleMesh circle(36);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(width / 2.0f, height / 2.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(200.0f, 200.0f, 1.0f));

	// --- Render loop ---
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// GUI example
		ImGui::Begin("Hello");
		ImGui::Text("This is ImGui + OpenGL + GLFW!");
		ImGui::End();

		// Rendering
		ImGui::Render();

		renderer.DrawPrimitive(rect, transform, {1.0f, 1.0f, 0.0f});
		renderer.DrawPrimitive(tri, transform, {0.0f, 1.0f, 1.0f});
		renderer.DrawPrimitive(circle, transform, {1.0f, 0.0f, 1.0f});

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// --- Cleanup ---
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}