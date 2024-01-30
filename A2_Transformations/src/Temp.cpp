#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define CheckCompilation(Shader) glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);\
		if (!success)\
		{\
			glGetShaderInfoLog(Shader, 512, NULL, infoLog);\
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;\
		}

#include "Minimal.h"

int  success;
char infoLog[512];

int msain()
{
	if (!glfwInit())
	{
		log("Failed to init glfw");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 640, height = 640;

	GLFWwindow* window = glfwCreateWindow(width, height, "test", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	CheckCompilation(vertexShader);

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 Color;\n"
		"void main()\n"
		"{\n"
		"   Color = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
		"}\0";

	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	CheckCompilation(fragmentShader);

	uint32_t shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.0f,  0.5f
	};

	uint32_t VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	uint32_t VBO;
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
	glEnableVertexAttribArray(0);

	//glBindVertexArray(0);

	while (!glfwWindowshouldClose(window))
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}