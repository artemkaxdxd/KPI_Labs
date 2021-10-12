#include "framework.h"
#include "pch.h"
#include "shape_editor.h"
#include "shape.h"


const int Size_Of_Array = 103;
Shape** pcshape = new Shape * [Size_Of_Array];
int createdobj = 0;
bool isPressed;


//ShapeObjectsEditor

ShapeObjectsEditor::ShapeObjectsEditor()
{
	pse = new PointEditor;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < createdobj; i++)
	{
		delete pcshape[i];
	}
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
	static const LPCSTR POINT_NAME = "Крапка";
	if (pse)
	{
		delete pse;
	}
	pse = new PointEditor;
	SetWindowTextA(hWnd, POINT_NAME);
}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd)
{
	static const LPCSTR LINE_NAME = "Лінія";
	if (pse)
	{
		delete pse;
	}
	pse = new LineEditor;
	SetWindowTextA(hWnd, LINE_NAME);
}

void ShapeObjectsEditor::StartRectangleEditor(HWND hWnd)
{
	static const LPCSTR RECTANGLE_NAME = "Прямокутник";
	if (pse)
	{
		delete pse;
	}
	pse = new RectangleEditor;
	SetWindowTextA(hWnd, RECTANGLE_NAME);
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd)
{
	static const LPCSTR ELLIPSE_NAME = "Овал";
	if (pse)
	{
		delete pse;
	}
	pse = new EllipseEditor;
	SetWindowTextA(hWnd, ELLIPSE_NAME);
}

void ShapeObjectsEditor::OnLMBdown(HWND hWnd)
{
	if (pse)
	{
		pse->OnLMBdown(hWnd);
	}
}

void ShapeObjectsEditor::OnLMBup(HWND hWnd)
{
	if (pse)
	{
		pse->OnLMBup(hWnd);
	}
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (pse && isPressed)
	{
		pse->OnMouseMove(hWnd);
	}
}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
	ShapeEditor* draw = new ShapeEditor;
	draw->OnPaint(hWnd);
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

void PointEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[createdobj] = Point;
	createdobj++;
	InvalidateRect(hWnd, NULL, TRUE);
}

//LineEditor

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
	hPen = CreatePen(PS_DOT, 1, black);
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

//RectangleEditor

void RectangleEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	RectangleShape* Rectangle = new RectangleShape;
	Rectangle->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
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
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Rectangle(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

//EllipseEditor

void EllipseEditor::OnLMBup(HWND hWnd)
{
	__super::OnLMBup(hWnd);
	EllipseShape* Ellipse = new EllipseShape;
	Ellipse->Set(x1, y1, x2, y2);
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
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, x1, y1, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Ellipse(hdc, x1, y1, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}