#pragma once
#include "pch.h"
#include "editor.h"
#include "Resource.h"


class ShapeEditor : public Editor
{
protected:
	long x1, x2, y1, y2;
public:
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	virtual void OnInitMenuPopup(HWND, WPARAM);
};

class ShapeObjectsEditor
{
private:
	ShapeEditor* pse;
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void StartPointEditor(HWND);
	void StartLineEditor(HWND);
	void StartRectangleEditor(HWND);
	void StartEllipseEditor(HWND);
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class PointEditor : public ShapeEditor
{
public:
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnLBup(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class LineEditor : public ShapeEditor
{
public:
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class RectangleEditor : public ShapeEditor
{
public:
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class EllipseEditor : public ShapeEditor
{
public:
	void OnLMBdown(HWND);
	void OnLMBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

