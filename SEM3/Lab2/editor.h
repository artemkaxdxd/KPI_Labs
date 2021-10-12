#pragma once
#include "pch.h"

class Editor
{
public:
	virtual void OnLMBdown(HWND) = 0;
	virtual void OnLMBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND) = 0;
};
