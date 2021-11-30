#include "framework.h"
#include "pch.h"
#include "Lab5.h"
#include "Resource.h"
#include "my_editor.h"
#include "toolbar.h"
#include "my_table.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

MyEditor& ED = ED.getInstance();
Toolbar toolbar;
MyTable* table = new MyTable;
std::string shapeDetails;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void OnStartApp(HWND hWnd) {
    toolbar.OnCreate(hWnd);
    ED.Start(new PointShape);
    table->ClearTableFile();
    table->CreateTable(hInst, hWnd);
    shapeDetails = "Shape\t\tx1\ty1\tx2\ty2";
    table->Add(shapeDetails);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB5);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        OnStartApp(hWnd);
        break;
    case WM_SIZE:
        toolbar.OnSize(hWnd);
        break;
    case WM_NOTIFY:
        toolbar.OnNotify(hWnd, lParam);
        break;
    case WM_LBUTTONDOWN:
        ED.OnLMBDown(hWnd);
        break;
    case WM_LBUTTONUP:
        ED.OnLMBUp(hWnd);
        shapeDetails = ED.GetDetails();
        table->Add(shapeDetails);
        break;
    case WM_MOUSEMOVE:
        ED.OnMouseMove(hWnd);
        break;
    case WM_INITMENUPOPUP:
        ED.OnInitMenuPopup(hWnd, wParam);
        break;
    case WM_PAINT:
        ED.OnPaint(hWnd, CurListSel-1);// -1 cuz first list line(element) is title
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_POINT:
            toolbar.OnToolPoint();
            ED.Start(new PointShape);
            break;
        case IDM_LINE:
            toolbar.OnToolLine();
            ED.Start(new LineShape);
            break;
        case IDM_RECTANGLE:
            toolbar.OnToolRectangle();
            ED.Start(new RectangleShape);
            break;
        case IDM_ELLIPSE:
            toolbar.OnToolEllipse();
            ED.Start(new EllipseShape);
            break;
        case IDM_LINEOO:
            toolbar.OnToolLineOO();
            ED.Start(new LineOOShape);
            break;
        case IDM_CUBE:
            toolbar.OnToolCube();
            ED.Start(new CubeShape);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_TABLE:
            ShowWindow(table->tableHwnd, SW_SHOW);
            break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}