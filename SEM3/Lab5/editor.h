#pragma once
#include "pch.h"

class Editor
{
public:
	virtual void OnLMBDown(HWND) = 0;
	virtual void OnLMBUp(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND, int) = 0;
};