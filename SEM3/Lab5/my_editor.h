#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"
#include "editor.h"
#include <string>

class MyEditor : public Editor
{
private:
	MyEditor() {}
	MyEditor(const MyEditor&);
	MyEditor& operator=(MyEditor&);
	Shape** pcshape = new Shape * [103];
	HWND handler;
	int size = 0;
	bool isPressed;
	int allMenus[6] = { IDM_POINT, IDM_LINE, IDM_RECTANGLE, IDM_ELLIPSE, IDM_LINEOO, IDM_CUBE };
public:
	static MyEditor& getInstance()
	{
		static MyEditor instance;
		return instance;
	}
	void Start(Shape*);
	void RemoveShape(int);
	void UpdateWindow();
	std::string GetDetails();
	void OnLMBDown(HWND);
	void OnLMBUp(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, int);
	void OnInitMenuPopup(HWND, WPARAM);
	~MyEditor();
	long x1, y1, x2, y2;
};