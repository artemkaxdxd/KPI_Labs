#include "shape.h"

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

void PointShape::Trail(HDC hdc) {}

int PointShape::InitMenuPopup()
{
	return ID_TOOL_POINT;
}

Shape* PointShape::Duplicate()
{
	return new PointShape();
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

void LineShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int LineShape::InitMenuPopup()
{
	return ID_TOOL_LINE;
}

Shape* LineShape::Duplicate()
{
	return new LineShape();
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

void RectangleShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int RectangleShape::InitMenuPopup()
{
	return ID_TOOL_RECTANGLE;
}

Shape* RectangleShape::Duplicate()
{
	return new RectangleShape();
}

void EllipseShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(pink);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

void EllipseShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Arc(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int EllipseShape::InitMenuPopup()
{
	return ID_TOOL_ELLIPSE;
}

Shape* EllipseShape::Duplicate()
{
	return new EllipseShape();
}

void LineOOShape::Show(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);
	EllipseShape::Set(x1, y1,
		x1 - lineooMerge, y1 - lineooMerge);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2, y2,
		x2 - lineooMerge, y2 - lineooMerge);
	EllipseShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void LineOOShape::Trail(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Trail(hdc);
	EllipseShape::Set(x1, y1,
		x1 - lineooMerge, y1 - lineooMerge);
	EllipseShape::Trail(hdc);
	EllipseShape::Set(x2, y2,
		x2 - lineooMerge, y2 - lineooMerge);
	EllipseShape::Trail(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

int LineOOShape::InitMenuPopup()
{
	return ID_TOOL_LINEOO;
}

Shape* LineOOShape::Duplicate()
{
	return new LineOOShape();
}

void CubeShape::Show(HDC hdc)
{
	x1 = xs1; 
	y1 = ys1; 
	x2 = xs2; 
	y2 = ys2;
	RectangleShape::Set(x1 - cubeMerge, y1 - cubeMerge,
		x1 + cubeMerge, y1 + cubeMerge);
	RectangleShape::Show(hdc);
	RectangleShape::Set(x2 - cubeMerge, y2 - cubeMerge,
		x2 + cubeMerge, y2 + cubeMerge);
	RectangleShape::Show(hdc);
	LineShape::Set(x1 - cubeMerge, y1 - cubeMerge,
		x2 - cubeMerge, y2 - cubeMerge);
	LineShape::Show(hdc);
	LineShape::Set(x1 - cubeMerge, y1 + cubeMerge,
		x2 - cubeMerge, y2 + cubeMerge);
	LineShape::Show(hdc);
	LineShape::Set(x1 + cubeMerge, y1 + cubeMerge,
		x2 + cubeMerge, y2 + cubeMerge);
	LineShape::Show(hdc);
	LineShape::Set(x1 + cubeMerge, y1 - cubeMerge,
		x2 + cubeMerge, y2 - cubeMerge);
	LineShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::Trail(HDC hdc)
{
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;
	RectangleShape::Set(x1 - cubeMerge, y1 - cubeMerge,
		x1 + cubeMerge, y1 + cubeMerge);
	RectangleShape::Trail(hdc);
	RectangleShape::Set(x2 - cubeMerge, y2 - cubeMerge,
		x2 + cubeMerge, y2 + cubeMerge);
	RectangleShape::Trail(hdc);
	LineShape::Set(x1 - cubeMerge, y1 - cubeMerge,
		x2 - cubeMerge, y2 - cubeMerge);
	LineShape::Trail(hdc);
	LineShape::Set(x1 - cubeMerge, y1 + cubeMerge,
		x2 - cubeMerge, y2 + cubeMerge);
	LineShape::Trail(hdc);
	LineShape::Set(x1 + cubeMerge, y1 + cubeMerge,
		x2 + cubeMerge, y2 + cubeMerge);
	LineShape::Trail(hdc);
	LineShape::Set(x1 + cubeMerge, y1 - cubeMerge,
		x2 + cubeMerge, y2 - cubeMerge);
	LineShape::Trail(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

int CubeShape::InitMenuPopup()
{
	return ID_TOOL_CUBE;
}

Shape* CubeShape::Duplicate()
{
	return new CubeShape();
}

Shape::~Shape() {};
