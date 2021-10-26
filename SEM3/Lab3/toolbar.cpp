#include "framework.h"
#include "pch.h"
#include "Lab3.h"
#include "toolbar.h"
#include "resource1.h"

HWND hwndToolBar = NULL;
int point, line, rectangle, ellipse, buttonToChange = 0;

void Toolbar::NotifyText(LPTOOLTIPTEXT lpttt, LPCSTR text) {
    lstrcpy(lpttt->szText, text);
}

void Toolbar::OnCreate(HWND hWnd)
{
    TBBUTTON tbb[5];
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TOOL_POINT;
    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;
    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECTANGLE;
    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;
    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_SEP;
    tbb[4].idCommand = 0;
    //WS_OVERLAPPED
    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4,
        hInst,
        IDB_BITMAP1,
        tbb,
        5,
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void Toolbar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void Toolbar::OnNewTool(int id) {
    SendMessage(hwndToolBar, TB_PRESSBUTTON, buttonToChange, 0);
    point = line = rectangle = ellipse = 0;
    buttonToChange = id;

}

void Toolbar::OnToolPoint()
{
    OnNewTool(ID_TOOL_POINT);
    point = !point;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
}

void Toolbar::OnToolLine()
{
    OnNewTool(ID_TOOL_LINE);
    line = !line;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
}

void Toolbar::OnToolRectangle()
{
    OnNewTool(ID_TOOL_RECTANGLE);
    rectangle = !rectangle;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECTANGLE, rectangle);
}

void Toolbar::OnToolEllipse()
{
    OnNewTool(ID_TOOL_ELLIPSE);
    ellipse = !ellipse;
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, ellipse);
}

void Toolbar::OnNotify(HWND hWnd, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    LPCSTR pText;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            NotifyText(lpttt, "Крапка");
            break;
        case ID_TOOL_LINE:
            NotifyText(lpttt, "Лінія");
            break;
        case ID_TOOL_RECTANGLE:
            NotifyText(lpttt, "Прямокутник");
            break;
        case ID_TOOL_ELLIPSE:
            NotifyText(lpttt, "Овал");
            break;
        default: NotifyText(lpttt, "Щось невідоме");
        }
    }
}