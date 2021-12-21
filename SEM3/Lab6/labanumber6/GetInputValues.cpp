#include "framework.h"
#include "GetInputValues.h"
#include "resource.h"
#include <string>

double n_MOD1;
double Min_MOD1;
double Max_MOD1;

const int allValues = 3;

HWND hWndDataCreator = NULL;
HWND hWndDataProcessor = NULL;

static INT_PTR CALLBACK InputValues_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

int SendCopyData(HWND hWndDest, HWND hWndSrc, void* lp, size_t cb);
int CreateObject3(HWND);
void OnOk(HWND);

int Func_MOD1(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUT), hWnd, InputValues_MOD1);
}

INT_PTR CALLBACK InputValues_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            OnOk(hDlg);
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
            break;
        }
        break;
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
    }
    break;
    default: break;
    }
    return FALSE;
}

void OnOk(HWND hDlg)
{
    WCHAR strn_MOD1[256];
    WCHAR strMin_MOD1[256];
    WCHAR strMax_MOD1[256];

    GetDlgItemText(hDlg, IDC_EDIT_N, (LPSTR)strn_MOD1, 256);
    GetDlgItemText(hDlg, IDC_EDIT_MIN, (LPSTR)strMin_MOD1, 256);
    GetDlgItemText(hDlg, IDC_EDIT_MAX, (LPSTR)strMax_MOD1, 256);

    std::string sn_MOD1((char*)strn_MOD1);
    std::string sMin_MOD1((char*)strMin_MOD1);
    std::string sMax_MOD1((char*)strMax_MOD1);

    try {
        n_MOD1 = stod(sn_MOD1);
        Min_MOD1 = stod(sMin_MOD1);
        Max_MOD1 = stod(sMax_MOD1);
    }
    catch (...)
    {
        MessageBox(hDlg, "Incorrect Format", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    if (n_MOD1 <= 0)
    {
        MessageBox(hDlg, "Incorrect number of elements", "ERROR", MB_OK | MB_ICONERROR);
        return;
    }

    try {
        if (Min_MOD1 <= Max_MOD1)
        {
            hWndDataCreator = FindWindow("OBJECT2", NULL);
            if (hWndDataCreator == NULL)
            {
                WinExec("Object2.exe", SW_SHOW);

                hWndDataCreator = FindWindow("OBJECT2", NULL);
            }
            double params[allValues] = { round(n_MOD1), Min_MOD1, Max_MOD1 };
            if (SendCopyData(hWndDataCreator, GetParent(hDlg), params, sizeof(params))) {
                if (CreateObject3(GetParent(hDlg))) {
                    return;
                }
                else
                {
                    throw std::exception("ERROR");
                }
            }
            else
            {
                throw std::exception("ERROR");
            }
            return;
        }
        else
        {
            MessageBox(hDlg, "Maximal value is smaller than minimal", "Error", MB_OK | MB_ICONERROR);
            return;
        }
    }
    catch (...)
    {
        PostMessage(hWndDataCreator, WM_CLOSE, NULL, NULL);
        MessageBox(hDlg, "Couldn't process your values", "Error", MB_ICONERROR | MB_OK);
    }
}

int SendCopyData(HWND hWndDest, HWND hWndSrc, void* lp, size_t cb)
{
    COPYDATASTRUCT cds{};
    cds.dwData = 1;
    cds.cbData = cb;
    cds.lpData = lp;
    return SendMessage(hWndDest, WM_COPYDATA, (WPARAM)hWndSrc, (LPARAM)&cds);
}

int CreateObject3(HWND hWnd) {
    hWndDataProcessor = FindWindow("OBJECT3", NULL);
    if (hWndDataProcessor == NULL)
    {
        WinExec("Object3.exe", SW_SHOW);

        hWndDataCreator = FindWindow("OBJECT3", NULL);
    }

    if (RedrawWindow(hWndDataProcessor, 0, 0, RDW_INVALIDATE) != 0)
    {
        return 1;
    }
    else
    {
        PostMessage(hWndDataProcessor, WM_CLOSE, NULL, NULL);
        return 0;
    }

}