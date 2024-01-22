#include "Minimal.h"

#include "GLFW/glfw3.h"

static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowshouldClose(window, GLFW_TRUE);
	}
}

int main()
{
	GLFWwindow* window;

	uint32_t width = 640;
	uint32_t height = 640;

	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(width, height, "Hello CG", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallBack);

	while (!glfwWindowshouldClose(window))
	{
		glClearColor(1.0f, 0.25f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	return 0;
}