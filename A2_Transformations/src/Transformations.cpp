#include "Minimal.h"

#include "Window.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main()
{
	auto window = std::shared_ptr<Window>(Window::Create());

	while (!window->IsOpen())
	{
		window->OnUpdate();
	}

	return 0;
}