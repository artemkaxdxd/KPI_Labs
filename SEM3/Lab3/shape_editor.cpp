#include "framework.h"
#include "pch.h"
#include "shape_editor.h"
#include "shape.h"

const int Size_Of_Array = 103;
Shape* pcshape[Size_Of_Array];
int createdobj = 0;
bool isPressed;

//ShapeObjectsEditor

ShapeObjectsEditor::ShapeObjectsEditor()
{
	pse = new PointEditor;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < createdobj; i++) delete pcshape[i];
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new PointEditor;
}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new LineEditor;
}

void ShapeObjectsEditor::StartRectangleEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new RectangleEditor;
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new EllipseEditor;
}

void ShapeObjectsEditor::OnLMBdown(HWND hWnd)
{
	if (pse) pse->OnLMBdown(hWnd);
}

void ShapeObjectsEditor::OnLMBup(HWND hWnd)
{
	if (pse) pse->OnLMBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (pse && isPressed) pse->OnMouseMove(hWnd);

}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
	ShapeEditor* draw = new ShapeEditor;
	draw->OnPaint(hWnd);
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {};

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	if (pse)
		pse->OnInitMenuPopup(hWnd, wParams);
}
//ShapeEditor

void ShapeEditor::OnMouseMove(HWND hWnd) {};

void ShapeEditor::OnLMBdown(HWND hWnd)
{
	isPressed = TRUE;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void ShapeEditor::OnLMBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;
}

void ShapeEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	if (createdobj >= Size_Of_Array) createdobj = 0;
	for (int i = 0; i < createdobj; i++)
	{
		if (pcshape[i])
		{
			pcshape[i]->Show(hdc);
		}
	}
	EndPaint(hWnd, &ps);
}

//PointEditor

void PointEditor::OnLMBdown(HWND hWnd) {
	__super::OnLMBdown(hWnd); // Calling a base-class implementation
}

void PointEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[createdobj] = Point;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);
}
void PointEditor::OnLBup(HWND hWnd) {
	__super::OnLMBup(hWnd); // Calling a base-class implementation
	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[createdobj] = Point;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void PointEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

//LineEditor

void LineEditor::OnLMBdown(HWND hWnd) {
	__super::OnLMBdown(hWnd); // Calling a base-class implementation
}

void LineEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	LineShape* Line = new LineShape;
	Line->Set(x1, y1, x2, y2);
	pcshape[createdobj] = Line;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void LineEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}
//RectangleEditor

void RectangleEditor::OnLMBdown(HWND hWnd) {
	__super::OnLMBdown(hWnd); // Calling a base-class implementation
}

void RectangleEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	RectangleShape* Rectangle = new RectangleShape;
	Rectangle->Set(x1, y1, x2, y2);
	pcshape[createdobj] = Rectangle;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);

}

void RectangleEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	Rectangle(hdc, x1, y1, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Rectangle(hdc, x1, y1, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);

}
void RectangleEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}
//EllipseEditor

void EllipseEditor::OnLMBdown(HWND hWnd) {
	__super::OnLMBdown(hWnd); // Calling a base-class implementation
}

void EllipseEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	EllipseShape* Ellipse = new EllipseShape;
	Ellipse->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
	pcshape[createdobj] = Ellipse;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void EllipseEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Ellipse(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
	}
}