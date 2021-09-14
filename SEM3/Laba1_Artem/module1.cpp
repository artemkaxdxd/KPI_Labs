#include "framework.h"
#include "resource1.h"

static WCHAR tempBuf[256];

static INT_PTR CALLBACK Work1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_LIST4, LB_ADDSTRING, 0, (LPARAM)"IP-01");
        SendDlgItemMessage(hDlg, IDC_LIST4, LB_ADDSTRING, 0, (LPARAM)"IP-02");
        SendDlgItemMessage(hDlg, IDC_LIST4, LB_ADDSTRING, 0, (LPARAM)"IP-03");
        SendDlgItemMessage(hDlg, IDC_LIST4, LB_ADDSTRING, 0, (LPARAM)"IP-04");
        SendDlgItemMessage(hDlg, IDC_LIST4, LB_ADDSTRING, 0, (LPARAM)"IP-05");

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            int idx = SendDlgItemMessage(hDlg, IDC_LIST4, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hDlg, IDC_LIST4, LB_GETTEXT, idx, (LPARAM)tempBuf);
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

int Func_MOD1(HINSTANCE hInst, HWND hWnd, WCHAR* dest) {
    if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1) == 1) {
        wsprintfW(dest, L"Selected group: %s", tempBuf);
        return 1;
    }
    return 0;
}