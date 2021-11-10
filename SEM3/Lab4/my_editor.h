#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"
#include "editor.h"

class MyEditor : public Editor 
{
public:
	void Start(Shape*);
	void OnLMBDown(HWND);
	void OnLMBUp(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
	~MyEditor();
	long x1, y1, x2, y2;
};