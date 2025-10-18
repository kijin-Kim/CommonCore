#include "Core/Application.h"
#include "Core/Layers/ImGuiLayer.h"
#include "Core/Layers/MainLayer.h"

int main()
{
	std::vector<std::unique_ptr<ILayer> > layers;
	layers.push_back(std::make_unique<MainLayer>());
	layers.push_back(std::make_unique<ImGuiLayer>());
	Application app(std::move(layers), 800, 600);
	app.Run();
}