// Object4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Object4.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::string text;
std::string parse;
std::vector<std::pair<int, int>> vectr;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
long                GetTextFromClipboard(HWND hWnd, long maxsize);
void                OnPaint(HWND, HDC, PAINTSTRUCT);
std::vector<std::pair<int, int>> GetVectrPair();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBJECT4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJECT4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBJECT4);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   AddClipboardFormatListener(hWnd);

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
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_BOTTOM, 200, 40, 900, 740, SWP_DEFERERASE);
        GetTextFromClipboard(hWnd, 65536);
        vectr = GetVectrPair();
        InvalidateRect(hWnd, 0, NULL);
    }
    break;
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            OnPaint(hWnd, hdc, ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLIPBOARDUPDATE:
        GetTextFromClipboard(hWnd, 65536);
        vectr = GetVectrPair();
        InvalidateRect(hWnd, 0, NULL);
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

long GetTextFromClipboard(HWND hWnd, long maxsize)
{
    HGLOBAL hglb;
    LPTSTR lptstr;
    long size, res;
    res = 0;
    char* dest = new char[maxsize];
    if (!IsClipboardFormatAvailable(CF_TEXT)) return 0;
    if (!OpenClipboard(hWnd)) return 0;
    hglb = GetClipboardData(CF_TEXT);
    if (hglb != NULL)
    {
        lptstr = (LPTSTR)GlobalLock(hglb);
        if (lptstr != NULL)
        {
            size = strlen((char*)lptstr);
            if (size > maxsize)
            {
                lptstr[maxsize] = 0;
                size = strlen((char*)lptstr);
            }
            strcpy_s(dest, maxsize, (char*)lptstr);
            res = size;
            GlobalUnlock(hglb);
        }
    }
    CloseClipboard();
    text = dest;
    return res;
}

std::vector<std::pair<int, int>> GetVectrPair()
{
    std::stringstream parse(text);
    parse << std::fixed;
    parse << std::setprecision(2);

    std::vector<double> parse_vctr;
    double number;

    while (parse >> number) parse_vctr.push_back(number);
    if (parse.fail() && !parse.eof()) return vectr;

    std::vector<std::pair<int, int>> res_vectr;
    std::pair<int, int> paird;
    for (auto i : parse_vctr)
    {
        paird.first = (int)i;
        paird.second = int((i - (int)i) * 100);
        res_vectr.push_back(paird);
    }

    return res_vectr;
}

void OnPaint(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{
    int graphwidth = 700;
    int graphheight = 600;
    int startPosX = 50;
    int startPosY = 650;
    int delimX;

    if (!vectr.empty()) delimX = graphwidth / vectr.size();
    int delimY = 50;

    HPEN hPen, hPenOld;
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hPenOld = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, startPosX, startPosY, NULL);
    LineTo(hdc, startPosX, 50);

    MoveToEx(hdc, startPosX, startPosY, NULL);
    LineTo(hdc, startPosX + 800, startPosY);

    for (int i = 1; i < 12; i++)
    {
        MoveToEx(hdc, startPosX - 5, startPosY - delimY * i, NULL);
        LineTo(hdc, startPosX + 5, startPosY - delimY * i);
    }
    
    if (!vectr.empty())
    {
        for (int i = 1; i < vectr.size(); i++)
        {
            MoveToEx(hdc, startPosX + delimX * i, startPosY + 5 , NULL);
            LineTo(hdc, startPosX + delimX * i, startPosY - 5);
        }

        for (int i = 0; i < vectr.size()-1; i++)
        {
            int fPosition = vectr[i].first * 50 + vectr[i].second / 2;
            MoveToEx(hdc, startPosX + delimX * i, startPosY - fPosition, NULL);
            int sPosition = vectr[i + 1].first * 50 + vectr[i + 1].second / 2;
            LineTo(hdc, startPosX + delimX * (i + 1), startPosY - sPosition);
        }
    }

    SelectObject(hdc, hPenOld);
    DeleteObject(hPen);
}
