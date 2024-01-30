#include "Minimal.h"

#include "Window.h"

int main()
{
	auto window = std::shared_ptr<Window>(Window::Create(WindowProps(640, 640)));

	while (!window->IsOpen())
	{
		window->OnUpdate();
	}

	return 0;
}