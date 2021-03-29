#include <windows.h>
#include <stdio.h>
#include <math.h>

#define width 1000
#define n 10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void drawNodes(int dx, int dy, int dtx, int nx[], int ny[], int hdc, int BPen, int nn[]) {
    for (int a = 0; a < 3; a++) {
        nx[a + 1] = nx[a] + 110;
        ny[a + 1] = ny[a];
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 3; a < 5; a++) {
        nx[a + 1] = nx[a];
        ny[a + 1] = ny[a] + 110;
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 5; a < 8; a++) {
        nx[a + 1] = nx[a] - 110;
        ny[a + 1] = ny[a];
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }

    for (int a = 8; a < 10; a++) {
        nx[a + 1] = nx[a];
        ny[a + 1] = ny[a] - 110;
        SelectObject(hdc, BPen);
        Ellipse(hdc, nx[a] - dx, ny[a] - dy, nx[a] + dx, ny[a] + dy);
        TextOut(hdc, nx[a] - dtx, ny[a] - dy / 2, nn[a], 1);
    }
}

void arrow(int px, int py, int dx, int dy, HDC hdc) {
    int lx, ly = py, rx = px, ry;
    if (dx == 0) return;
    else lx = px + (dx / abs(dx)) * 15;
    if (dy == 0) {
        ly = py - 15;
        ry = py + 15;
        lx = px + (15 * dx / abs(dx));
        rx = lx;
    }
    else ry = py + (dy / abs(dy)) * 15;
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void paintLine1(int matrix[n][n], HDC hdc, int dx, int dy, int nx[], int ny[]) {
    int  radius = 16, divine = 1, xDif, yDif;
    float koef = 1.0 - 0 * 0.02 - 3 * 0.005 - 0.25;
    for (int start = 0; start < n; start++) {
        for (int end = 0; end < n; end++) {
            if (matrix[start][end] == 1) {
                xDif = nx[start] - nx[end];
                yDif = ny[start] - ny[end];
                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                dx = xDif / koef;
                dy = yDif / koef;
                if (start == end) {
                    MoveToEx(hdc, nx[end], ny[end], NULL);
                    LineTo(hdc, nx[end] + 40, ny[end] + 10);
                    LineTo(hdc, nx[end] + 40, ny[end] + 40);
                    LineTo(hdc, nx[end] + 10, ny[end] + 40);
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + 2, ny[end] + 13, 2, 13, hdc);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                        dx = xDif / 2 / koef;
                        dy = (yDif - 35) / koef;
                    }
                    else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                        dx = xDif / 2 / koef;
                        dy = yDif / koef;
                    }
                    LineTo(hdc, nx[end], ny[end]);
                    arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                }
            }
        }
    }
}

void paintLine2(int matrix[n][n], HDC hdc, int dx, int dy, int nx[], int ny[]) {
    int  radius = 16, divine = 1, xDif, yDif;
    float koef = 1.0 - 0 * 0.02 - 3 * 0.005 - 0.25;
    for (int start = 0; start < n; start++) {
        for (int end = 0; end < n; end++) {
            if (matrix[start][end] == 1) {
                xDif = nx[start] - nx[end];
                yDif = ny[start] - ny[end];
                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                dx = xDif / koef;
                dy = yDif / koef;
                if (start == end) {
                    MoveToEx(hdc, nx[end], ny[end], NULL);
                    LineTo(hdc, nx[end] + 40, ny[end] + 10);
                    LineTo(hdc, nx[end] + 40, ny[end] + 40);
                    LineTo(hdc, nx[end] + 10, ny[end] + 40);
                    LineTo(hdc, nx[end], ny[end]);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);
                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                        dx = xDif / 2 / koef;
                        dy = (yDif - 35) / koef;
                    }
                    else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                        dx = xDif / 2 / koef;
                        dy = yDif / koef;
                    }
                    LineTo(hdc, nx[end], ny[end]);
                }
            }
        }
    }
}

char ProgName[] = "Lab 3";

int matrix[n][n] = {
    {0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 1} };

int matrixSim[n][n] = {
    {0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 1},
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 1} };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = WHITE_BRUSH; //LTGRAY_BRUSH; цвет фона окна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName, //Имя программы
        L"Lab 3 Bondarchuk A.", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        100, //положение окна на экране по х
        100, //положение по у
        width + 650, //ширина окна 
        800, //высота окна
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
        TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
        DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
    }

    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
    WPARAM wParam, LPARAM lParam) {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

    switch (messg) {
        case WM_PAINT:

            hdc = BeginPaint(hWnd, &ps);
            char* nn[n] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
            int nx[n + 1] = { 100 },
                ny[n + 1] = { 100 },
                nx2[n + 1] = { 800 },
                ny2[n + 1] = { 100 };
            int dx = 16, dy = 16, dtx = 5;

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255)); // border
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5)); // line

            drawNodes(dx, dy, dtx, nx, ny, hdc, BPen, nn);
            drawNodes(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);

            SelectObject(hdc, KPen);

            paintLine1(matrix, hdc, dx, dy, nx, ny);
            paintLine2(matrixSim, hdc, dx, dy, nx2, ny2);

            drawNodes(dx, dy, dtx, nx, ny, hdc, BPen, nn);
            drawNodes(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}