#include "framework.h"
#include "resource2.h"

static WCHAR tempBuf[255];

static INT_PTR CALLBACK Work2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemText(hDlg, IDC_EDIT2, (LPSTR)tempBuf, sizeof(tempBuf));
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)FALSE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int Func_MOD2(HINSTANCE hInst, HWND hWnd, WCHAR* dest) {
    if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Work2) == 1) {
        lstrcpyW(dest, tempBuf);
        return 1;
    }
    return 0;
}