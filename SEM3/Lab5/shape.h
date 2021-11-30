#include "pch.h"
#include "colors.h"
#include "toolbar.h"
#include <string>

class Shape
{
protected:
	int xs1, ys1, xs2, ys2;
	int conture;
public:
	void Set(int x1, int y1, int x2, int y2);
	int* GetCoords();
	virtual void Show(HDC, int) = 0;
	virtual void Trail(HDC) = 0;
	virtual int InitMenuPopup() = 0;
	virtual Shape* Duplicate() = 0;
	virtual std::string GetName() = 0;
	~Shape();
};

class PointShape : public Shape
{
public:
	virtual void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};

class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};

class CubeShape : public RectangleShape, public LineShape
{
public:
	void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};

class LineOOShape : public LineShape, public EllipseShape
{
public:
	void Show(HDC, int);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
	virtual std::string GetName();
};