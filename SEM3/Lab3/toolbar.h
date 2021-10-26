#pragma once

#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECTANGLE               32807
#define ID_TOOL_ELLIPSE                 32809
#define IDC_MY_TOOLBAR                  32811

class Toolbar
{
private:
	static void OnNewTool(int id);
	static void NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text);
public:
	void OnSize(HWND hWnd);
	void OnCreate(HWND hWnd);
	void OnNotify(HWND hWnd, LPARAM lParam);
	void OnToolPoint();
	void OnToolLine();
	void OnToolRectangle();
	void OnToolEllipse();
};
