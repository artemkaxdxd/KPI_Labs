#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "toolbar.h"

const int Size_Of_Array = 103;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;
int allMenus[6] = { IDM_POINT, IDM_LINE, IDM_RECTANGLE, IDM_ELLIPSE, IDM_LINEOO, IDM_CUBE };

MyEditor::~MyEditor()
{
	for (int i = 0; i < size; i++)
	{
		delete pcshape[i];
	}
	delete* pcshape;
}

void MyEditor::Start(Shape* shape)
{
	pcshape[size] = shape;
}

void MyEditor::OnLMBDown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void MyEditor::OnLMBUp(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[size]->Set(x1, y1, x2, y2);
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[size] = pcshape[size - 1]->Duplicate();
}

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (isPressed)
	{
		POINT pt;
		HDC hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trail(hdc);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trail(hdc);
		ReleaseDC(hWnd, hdc);
	}
}

void MyEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < size; i++)
	{
		if (pcshape[i])
		{
			pcshape[i]->Show(hdc);
		}
	}
	EndPaint(hWnd, &ps);
}

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);

	if ((HMENU)wParams == hSubMenu)
	{
		for (auto& item : allMenus)
		{
			CheckMenuItem(hSubMenu, item, MF_UNCHECKED);
		}

		switch (pcshape[size]->InitMenuPopup())
		{
		case ID_TOOL_POINT:
			CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
			break;
		case ID_TOOL_LINE:
			CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
			break;
		case ID_TOOL_RECTANGLE:
			CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
			break;
		case ID_TOOL_ELLIPSE:
			CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
			break;
		case ID_TOOL_LINEOO:
			CheckMenuItem(hSubMenu, IDM_LINEOO, MF_CHECKED);
			break;
		case ID_TOOL_CUBE:
			CheckMenuItem(hSubMenu, IDM_CUBE, MF_CHECKED);
			break;
		}
	}
}