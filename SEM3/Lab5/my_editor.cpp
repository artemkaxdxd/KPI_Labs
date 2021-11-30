#include "my_editor.h"

MyEditor::~MyEditor()
{
	delete[] pcshape;
}

void MyEditor::RemoveShape(int n)
{
	delete pcshape[n];
}

void MyEditor::UpdateWindow()
{
	InvalidateRect(handler, NULL, TRUE);
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

void MyEditor::OnPaint(HWND hWnd, int n)
{
	if (!handler) handler = hWnd;
	PAINTSTRUCT ps;
	HDC hdc;
	int defaultPen = 1;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < size; i++)
	{
		if (pcshape[i])
		{
			defaultPen = n == i ? 0 : 1;
			pcshape[i]->Show(hdc, defaultPen);
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

std::string MyEditor::GetDetails() {
	char str[40];
	int* arr = pcshape[size - 1]->GetCoords();
	sprintf_s(str, "%s\t\t%d\t%d\t%d\t%d", pcshape[size-1]->GetName().c_str(), arr[0], arr[1], arr[2], arr[3]);
	return (std::string)str;
}