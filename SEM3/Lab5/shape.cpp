#include "shape.h"

const int lineooMerge = 20;
int __x1, __x2, __y1, __y2;


void Shape::Set(int Sx1, int Sy1, int Sx2, int Sy2)
{
	xs1 = Sx1;
	ys1 = Sy1;
	xs2 = Sx2;
	ys2 = Sy2;
}

int* Shape::GetCoords()
{
	int arr[4] = { xs1, ys1, xs2, ys2 };
	return arr;
}

void PointShape::Show(HDC hdc, int defPen)
{
	COLORREF curColor = defPen == 1 ? black : blue;
	SetPixel(hdc, xs1, ys1, curColor);
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

std::string PointShape::GetName()
{
	return (std::string)"Point";
}

void LineShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;
	COLORREF curColor = defPen == 1 ? black : blue;
	hPen = CreatePen(PS_SOLID, 1, curColor);
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

std::string LineShape::GetName()
{
	return (std::string)"Line";
}


void RectangleShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	COLORREF curColor = defPen == 1 ? black : blue;
	hPen = CreatePen(PS_SOLID, 1, curColor);
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

std::string RectangleShape::GetName()
{
	return (std::string)"Rect";
}

void EllipseShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	COLORREF curColor = defPen == 1 ? black : blue;
	hPen = CreatePen(PS_SOLID, 1, curColor);
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

std::string EllipseShape::GetName()
{
	return (std::string)"Ellipse";
}

void LineOOShape::Show(HDC hdc, int defPen)
{
	__x1 = xs1;
	__y1 = ys1;
	__x2 = xs2;
	__y2 = ys2;
	LineShape::Set(__x1, __y1, __x2, __y2);
	LineShape::Show(hdc, defPen);
	EllipseShape::Set(__x1, __y1,
		__x1 - lineooMerge, __y1 - lineooMerge);
	EllipseShape::Show(hdc, defPen);
	EllipseShape::Set(__x2, __y2,
		__x2 - lineooMerge, __y2 - lineooMerge);
	EllipseShape::Show(hdc, defPen);
	LineShape::Set(__x1, __y1, __x2, __y2);
}

void LineOOShape::Trail(HDC hdc)
{
	__x1 = xs1;
	__y1 = ys1;
	__x2 = xs2;
	__y2 = ys2;
	LineShape::Set(__x1, __y1, __x2, __y2);
	LineShape::Trail(hdc);
	EllipseShape::Set(__x1, __y1,
		__x1 - lineooMerge, __y1 - lineooMerge);
	EllipseShape::Trail(hdc);
	EllipseShape::Set(__x2, __y2,
		__x2 - lineooMerge, __y2 - lineooMerge);
	EllipseShape::Trail(hdc);
	LineShape::Set(__x1, __y1, __x2, __y2);
}

int LineOOShape::InitMenuPopup()
{
	return ID_TOOL_LINEOO;
}

Shape* LineOOShape::Duplicate()
{
	return new LineOOShape();
}

std::string LineOOShape::GetName()
{
	return (std::string)"LineOO";
}

void CubeShape::Show(HDC hdc, int defPen)
{
	__x1 = xs1;
	__y1 = ys1;
	__x2 = xs2;
	__y2 = ys2;
	RectangleShape::Set(__x1 - conture, __y1 - conture,
		__x1 + conture, __y1 + conture);
	RectangleShape::Show(hdc, defPen);
	RectangleShape::Set(__x2 - conture, __y2 - conture,
		__x2 + conture, __y2 + conture);
	RectangleShape::Show(hdc, defPen);
	LineShape::Set(__x1 - conture, __y1 - conture,
		__x2 - conture, __y2 - conture);
	LineShape::Show(hdc, defPen);
	LineShape::Set(__x1 - conture, __y1 + conture,
		__x2 - conture, __y2 + conture);
	LineShape::Show(hdc, defPen);
	LineShape::Set(__x1 + conture, __y1 + conture,
		__x2 + conture, __y2 + conture);
	LineShape::Show(hdc, defPen);
	LineShape::Set(__x1 + conture, __y1 - conture,
		__x2 + conture, __y2 - conture);
	LineShape::Show(hdc, defPen);
	LineShape::Set(__x1, __y1, __x2, __y2);
}

void CubeShape::Trail(HDC hdc)
{
	__x1 = xs1; __y1 = ys1; __x2 = xs2; __y2 = ys2;
	conture = __x2 - __x1;
	RectangleShape::Set(__x1 - conture, __y1 - conture,
		__x1 + conture, __y1 + conture);
	RectangleShape::Trail(hdc);
	RectangleShape::Set(__x2 - conture, __y2 - conture,
		__x2 + conture, __y2 + conture);
	RectangleShape::Trail(hdc);
	LineShape::Set(__x1 - conture, __y1 - conture,
		__x2 - conture, __y2 - conture);
	LineShape::Trail(hdc);
	LineShape::Set(__x1 - conture, __y1 + conture,
		__x2 - conture, __y2 + conture);
	LineShape::Trail(hdc);
	LineShape::Set(__x1 + conture, __y1 + conture,
		__x2 + conture, __y2 + conture);
	LineShape::Trail(hdc);
	LineShape::Set(__x1 + conture, __y1 - conture,
		__x2 + conture, __y2 - conture);
	LineShape::Trail(hdc);
	LineShape::Set(__x1, __y1, __x2, __y2);
}

int CubeShape::InitMenuPopup()
{
	return ID_TOOL_CUBE;
}

Shape* CubeShape::Duplicate()
{
	return new CubeShape();
}

std::string CubeShape::GetName()
{
	return (std::string)"Cube";
}

Shape::~Shape() {};
