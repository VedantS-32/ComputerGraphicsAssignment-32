#include "Minimal.h"
#include "glm/glm.hpp"

#include "Application.h"

int main()
{
	auto application = std::make_shared<Application>();

	application->Run();

	return 0;
}