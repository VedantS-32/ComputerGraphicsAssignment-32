#pragma once

#include "Minimal.h"
#include "Input.h"

class WindowsInput : public Input
{
protected:
	virtual bool IsKeyPressedImpl(int keycode) override;
	virtual bool IsMouseButtonPressedImpl(int button) override;
	virtual bool IsMouseButtonReleasedImpl(int button) override;
	virtual std::pair<float, float> GetMousePositionImpl() override;
	virtual std::pair<float, float> GetMouseScrollOffsetImpl() override;
};