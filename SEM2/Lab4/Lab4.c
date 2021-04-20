#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define N 10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

wchar_t ProgName[] = L"Лабораторна робота 4";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName,
        L"LAB 4 Bondarchuk A.",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        1200,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

void arrow(int px, int py, int dx, int dy, HDC hdc) {
    int lx, ly = py, rx = px, ry;
    if (dx == 0 && dy == 0) return;
    if (dx == 0) {
        ly = py + (15 * dy / abs(dy));
        ry = ly;
        lx = px - 15;
        rx = px + 15;
    }
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

//MATRIX SIMETRICAL
void simMatrix(int A[N][N], int* B[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] == 1) {
                B[j][i] = 1;
                B[i][j] = 1;
            }
        }
    }
}

void generateMtx(int* matrix[N][N], float k) {
    int element;
    float num;
    srand(0503);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = (rand() / (float)RAND_MAX * 2) * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
        }
    }
}

//sub-edges
void printEdge(int B[N][N], HDC hdc, int height, int type) {
    char text[9];
    int counter[N] = { 0 };
    int counter2[N] = { 0 };
    int checker = -1, flag = 1, isolatedFlag = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] == 1) {
                if (i == j && !type) counter[i]++;
                counter[i]++;
                if (type) counter2[j]++;
            }
        }
        if (checker == -1) checker = counter[i];
        else if (checker != counter[i]) flag = 0;
        sprintf_s(text, 8, "deg%d= %d", i, counter[i]);
        TextOutA(hdc, 5 + 80 * i, height, text, 8);
    }
    if (type) {
        for (int count = 0; count < N;count++) {
            sprintf_s(text, 9, "deg%d-= %d", count, counter2[count]);
            TextOutA(hdc, 5 + 80 * count, height + 20, text, 9);

            if (counter[count] == 0 && counter2[count] == 0) {
                sprintf_s(text, 9, "Isolat=%d", count);
                TextOutA(hdc, 5, height - 320, text, 9);
            }

            if ((counter[count] == 1 && counter2[count] == 0) || (counter[count] == 0 && counter2[count] == 1)) {
                sprintf_s(text, 9, "Self = %d", count);
                TextOutA(hdc, 5, height - 340 - 10 * count, text, 9);
            }
        }
    }
    if (flag) {
        sprintf_s(text, 9, "Odinr=%d", checker);
        TextOutA(hdc, 5, height + 300, text, 9);
    }
}

void drawgraph(HDC hdc, int startA[N][N], int components[N][N]) {
    int xPos[N] = { 75,275,275,75,150,200,200,150,50,300 };
    int yPos[N] = { 75,75,225,225,50,50,250,250,150,150 };
    int drawVert[N] = { 0,0,0,0,0,0,0,0,0,0 };
    char* nn[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    int dtx = 5, radius = 16, end, xDif, yDif, dx, dy, koef;

    for (int i = 0;i < N; i++) {
        for (int j = 0;j < N; j++) {
            if (components[i][j] == 0) continue;
            for (int count = 0;count < N;count++) {
                if (startA[j][count]) {
                    for (int count2 = 0; count2 < N;count2++) {
                        if (components[count2][count]) {
                            MoveToEx(hdc, xPos[i], yPos[i], NULL);
                            LineTo(hdc, xPos[count2], yPos[count2]);
                            xDif = xPos[i] - xPos[count2];
                            yDif = yPos[i] - yPos[count2];
                            if (xDif == 0 && yDif == 0) {
                                dx = 0;
                                dy = 0;
                            }
                            else {
                                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                                dx = xDif / koef;
                                dy = yDif / koef;
                            }
                            arrow(xPos[count2] + dx, yPos[count2] + dy, dx, dy, hdc);
                        }
                    }
                }
            }
            drawVert[i] = 1;
        }
    }
    for (int i = 0;i < N;i++) {
        if (drawVert[i]) {
            Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
            TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 1);
        }
    }
}

void powMatrix(HDC hdc, int A[N][N], int startA[N][N], int reachA[N][N], int length) {
    int num, counter = 1, countery = 1;
    char text[11];
    int newA[N][N];
    int connA[N][N] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
    };

    int components[N][N] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    int usedVerticles[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    //multiply matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = 0;
            for (int count = 0; count < N; count++) {
                num += A[i][count] * startA[count][j];
            }
            newA[i][j] = num;
            reachA[i][j] += num;
        }
    }
    //all tasks operations
    if (length == 2) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                //print ways of power2
                /*if (startA[i][j] == 1) {
                    for (int count = 0; count < N; count++) {
                        if (startA[j][count] == 1) {
                                sprintf_s(text, 8, "%d->%d->%d", i, j, count);
                                TextOutA(hdc, 5 + 65 * counter, 600 + 20*countery, text, 8);
                                counter++;
                                if ((float)counter / 17 > 1) {
                                    countery++;
                                    counter = 1;
                                }
                        }
                    }
                }*/

                //print ways of power3
                /*if (startA[i][j] == 1) {
                    for (int count = 0; count < N; count++) {
                        if (startA[j][count] == 1) {
                            for (int count2 = 0; count2 < N; count2++) {
                                if (startA[count][count2] == 1) {
                                    sprintf_s(text, 11, "%d->%d->%d->%d", i, j, count, count2);
                                    TextOutA(hdc, 0 + 80 * counter, 540 + 20 * countery, text, 11);
                                    counter++;
                                    if ((float)counter / 17 > 1) {
                                        countery++;
                                        counter = 1;
                                    }
                                }
                            }
                        }
                    }
                }*/

                //reach matrix
                reachA[i][j] += startA[i][j];
                if (reachA[i][j] >= 1) reachA[i][j] = 1;
                else {
                    connA[i][j] = 0;
                    connA[j][i] = 0;
                }
                //print reach matrix
                sprintf_s(text, 2, "%d", reachA[i][j]);
                TextOutA(hdc, 5 + 25 * j, 400 + 20 * i, text, 1);


            }
        }

        //print connection matrix
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                sprintf_s(text, 2, "%d", connA[i][j]);
                TextOutA(hdc, 350 + 25 * j, 400 + 20 * i, text, 1);
            }
        }
        countery = 0;
        //find components
        for (int count = 0; count < N; count++) {
            counter = 1;
            for (int i = 0; i < N; i++) {
                if (usedVerticles[i] == 1) continue;
                for (int j = 0; j < N; j++) {
                    if (connA[count][j] != connA[i][j]) break;
                    if (j == N - 1) {
                        usedVerticles[i] = 1;
                        components[countery][i] = 1;
                        sprintf_s(text, 3, "K%d", countery);
                        TextOutA(hdc, 10, 250 + 25 * countery, text, 2);
                        sprintf_s(text, 2, "%d", i);
                        TextOutA(hdc, 20 + 20 * counter, 250 + 25 * countery, text, 1);
                        counter++;
                    }
                }
            }
            for (int i = 0; i < N; i++) {
                if (components[countery][i]) countery++;
            }
        }
        //draw cond graph
        drawgraph(hdc, startA, components);
    }

    if (length > 2) powMatrix(hdc, newA, startA, reachA, length - 1);
}

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

void paintLine(int matrix[N][N], HDC hdc, int dx, int dy, int nx[], int ny[], float koef, int oriented) {
    int  radius = 16, divine = 1, xDif, yDif;
    for (int start = 0; start < N; start++) {
        for (int end = 0; end < N; end++) {
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
                    if (oriented) arrow(nx[end] + 2, ny[end] + 13, 2, 13, hdc);
                }
                else if (matrix[start][end] == 1 && matrix[end][start] == 1) {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if (oriented) LineTo(hdc, nx[end] + xDif / 2 + (20 * divine), ny[end] + yDif / 2 + (20 * divine));
                    LineTo(hdc, nx[end], ny[end]);
                    if (oriented) arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                    divine = -divine;
                }
                else {
                    MoveToEx(hdc, nx[start], ny[start], NULL);
                    if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 200) {
                        LineTo(hdc, nx[end] + xDif / 2, ny[end] - 25);
                    }
                    else if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
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
                    if (oriented) arrow(nx[end] + dx, ny[end] + dy, dx, dy, hdc);
                }
            }
        }
    }
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        int A[N][N];
        int B[N][N];
        char* nn[N] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        int xPos[10];
        int yPos[10];
        int dtx = 5, radius = 16, startX = 100, divine = 1, divine2 = -1, dx = 16, dy = 16, xDif, yDif;
        int OrientGraph = 1;// 1 - Oriented Graph | 0- Not oriented
        int diagonalA[N][N] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
        };

        int nx[N + 1] = { 100 },
            ny[N + 1] = { 100 },
            nx2[N + 1] = { 550 },
            ny2[N + 1] = { 100 };
        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        SelectObject(hdc, BlackPen);

        //Task 4
        //float koef = 1.0 - 0 * 0.1 - 3 * 0.01 - 0.3;
        //generateMtx(A, (1.0 - 0 * 0.005 - 3 * 0.005 - 0.27));
        //simMatrix(A, B);
        ////printEdge(A, hdc, 600, 1); //sub-pow-nodes
        //powMatrix(hdc, A, A, diagonalA, N - 1);

        
        //Task 2 + 3
        float koef = 1.0 - 0 * 0.005 - 3 * 0.005 - 0.27;
        generateMtx(A, (1.0 - 0 * 0.005 - 3 * 0.005 - 0.27));
        simMatrix(A, B);
        printEdge(A, hdc, 600,1);
        printEdge(B, hdc, 10,0);
        
        drawNodes(dx, dy, dtx, nx, ny, hdc, BPen, nn);
        drawNodes(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);

        SelectObject(hdc, BlackPen);

        paintLine(A, hdc, dx, dy, nx, ny, koef, 1);
        paintLine(B, hdc, dx, dy, nx2, ny2, koef, 0);

        drawNodes(dx, dy, dtx, nx, ny, hdc, BPen, nn);
        drawNodes(dx, dy, dtx, nx2, ny2, hdc, BPen, nn);
        SelectObject(hdc, BPen);
        
        

        for (int i = 0;i < N;i++) {
            Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
            TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 1);
        }
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