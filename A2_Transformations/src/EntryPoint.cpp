#include "Minimal.h"
#include "glm/glm.hpp"


#include "Window.h"

int main()
{
	auto window = std::shared_ptr<Window>(Window::Create(WindowProps(1280, 720)));

	while (!window->IsOpen())
	{
		window->OnUpdate();
	}

	return 0;
}