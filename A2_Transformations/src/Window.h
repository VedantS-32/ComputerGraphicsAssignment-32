#pragma once

#include "Minimal.h"
#include "GLFW/glfw3.h"

struct WindowProps
{
	unsigned int Width;
	unsigned int Height;
	std::string Title;

	WindowProps(unsigned int width = 1280, unsigned int height = 720, std::string title = "GLTransformations")
		: Width(width), Height(height), Title(title) {}
};

class Window
{
public:
	virtual ~Window() {}

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	static Window* Create(const WindowProps& props = WindowProps());
	virtual inline bool IsOpen() = 0;
	virtual void OnUpdate() = 0;
};