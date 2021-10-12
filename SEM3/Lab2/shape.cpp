#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"


void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, black);
}

void LineShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2); 			     

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectangleShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(NULL_BRUSH);
	hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};
