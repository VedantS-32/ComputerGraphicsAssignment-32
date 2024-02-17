#pragma once

class ImGuiLayer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void Begin();
	void OnImGuiRender();
	void End();
};