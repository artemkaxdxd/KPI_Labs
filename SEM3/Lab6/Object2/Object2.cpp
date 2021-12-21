// Object2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Object2.h"
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

double n_MOD2;
double Min_MOD2;
double Max_MOD2;



std::random_device rd;
std::mt19937 gen;
std::vector<double> vectr;

std::string formattedText;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                OnCopyData(HWND, WPARAM, LPARAM);
void                CreateVector(int, double, double);
int                 PutTextToClipboard(HWND, const char*);
void                OnPaint(HWND, HDC, PAINTSTRUCT);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringA(hInstance, IDS_APP_TITLE, (LPSTR)szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBJECT2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, 250, 250, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_BOTTOM, 40, 40, 300, 300, SWP_DEFERERASE);
        break;
    }
    case WM_COPYDATA:
        OnCopyData(hWnd, wParam, lParam);
        InvalidateRect(hWnd, 0, TRUE);
        return 1;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hWnd, hdc, ps);
            EndPaint(hWnd, &ps);
            
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COPYDATASTRUCT* cds;
    cds = (COPYDATASTRUCT*)lParam;
    double* p = (double*)cds->lpData;
    n_MOD2 = p[0];
    Min_MOD2 = p[1];
    Max_MOD2 = p[2];

    CreateVector(n_MOD2, Min_MOD2, Max_MOD2);
    
    InvalidateRect(hWnd, NULL, TRUE);
    if (RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW)) PutTextToClipboard(hWnd, formattedText.c_str());
}

void CreateVector(int n, double Min, double Max)
{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(2);
    formattedText = "";
    gen.seed(rd());
    std::uniform_real_distribution<double> distr(Min, Max);
    double randgener;
    for (int i = 0; i < n; i++)
    {
        randgener = distr(gen);
        vectr.push_back(randgener);

        streamObj << randgener << ' ';
    }

    formattedText = streamObj.str();
}

int PutTextToClipboard(HWND hWnd, const char* src)
{
    HGLOBAL hglbCopy;
    BYTE* pTmp;
    long len;
    if (src == NULL) return 0;
    if (src[0] == 0) return 0;
    len = strlen(src);
    hglbCopy = GlobalAlloc(GHND, len + 1);
    if (hglbCopy == NULL) return FALSE;
    pTmp = (BYTE*)GlobalLock(hglbCopy);
    memcpy(pTmp, src, len + 1);
    GlobalUnlock(hglbCopy);
    if (!OpenClipboard(hWnd))
    {
        GlobalFree(hglbCopy);
        return 0;
    }
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hglbCopy);
    CloseClipboard();
    return 1;
}

void OnPaint(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{
    RECT rc = { 0 };
    GetClientRect(hWnd, &rc);
    SetTextColor(hdc, RGB(0, 0, 0));
    char* cstr = new char[formattedText.size() + 1];

    if (formattedText != "") {
        strcpy_s(cstr, formattedText.size() + 1, formattedText.c_str());
        DrawTextA(hdc, cstr, -1, &rc, DT_TOP | DT_WORDBREAK);
    }
}