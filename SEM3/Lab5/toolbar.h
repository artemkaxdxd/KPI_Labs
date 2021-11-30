#pragma once
#include "pch.h"
#include "framework.h"
#include "Lab5.h"
#include "resource1.h"

#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECTANGLE               32807
#define ID_TOOL_ELLIPSE                 32809
#define ID_TOOL_LINEOO					32810
#define ID_TOOL_CUBE					32811
#define IDC_MY_TOOLBAR                  32822

class Toolbar
{
private:
	HWND hwndToolBar = NULL;
	int point, line, rectangle, ellipse, lineoo, cube, buttonToChange = 0;
	void OnNewTool(int id);
	void NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text);
public:
	void OnSize(HWND hWnd);
	void OnCreate(HWND hWnd);
	void OnNotify(HWND hWnd, LPARAM lParam);
	void OnToolPoint();
	void OnToolLine();
	void OnToolRectangle();
	void OnToolEllipse();
	void OnToolLineOO();
	void OnToolCube();
};
