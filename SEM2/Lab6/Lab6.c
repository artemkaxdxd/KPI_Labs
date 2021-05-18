#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define N 10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

wchar_t  ProgName[] = L"Lab 6 Bondarchuk A."; //имя программы

struct stack {
    int array[N];
    int top;
};

struct stack* initStack() {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->top = 0;
    return stack;
}

void pushStack(struct stack* stack, int value) {
    if (stack->top < N) {
        stack->array[stack->top] = value;
        stack->top++;
    }
}

void flush(struct stack* stack) {
    stack->top--;
}

int top(struct stack* stack) {
    if (stack->top > 0)
        return stack->array[stack->top - 1];
    else return -1;
}

int isEmptyStack(struct stack* stack) {
    if (stack->top == 0)
        return 1;
    else
        return 0;
}

int DFS(int A[N][N], int start, int end) {//depth
    int treeMatrix[N][N] = { 0 };
    struct stack* s = initStack();
    int visited[N] = { 0 };
    int curVertex;
    pushStack(s, start);
    visited[start] = 1;
    while (!isEmptyStack(s)) {
        curVertex = top(s);
        for (int i = 0; i < N; i++) {
            if (A[curVertex][i]) {
                if (i == end) return 1;
                if (visited[i] == 0) {
                    visited[i] = 1;
                    treeMatrix[curVertex][i] = 1;
                    pushStack(s, i);
                    break;
                }
            }
            if (i == N - 1) {
                flush(s);
            }
        }
    }
    return 0;
}

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
        L"Lab 6 Bondarchuk A.",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        1200,
        900,
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

void paintLines(HDC hdc, int B[N][N], int nx[N], int ny[N], int start, int end) {
    int xDif = nx[start] - nx[end];
    int yDif = ny[start] - ny[end];
    char text[5];
    sprintf_s(text, sizeof(text), "%d", B[start][end]);
    if (B[start][end]) {
        if (start == end) {//LOOP check
            MoveToEx(hdc, nx[end], ny[end], NULL);
            Arc(hdc, nx[end], ny[end] - 40, nx[end] + 40, ny[end], nx[end] + 10, ny[end], nx[end], ny[end] - 10);
            TextOutA(hdc, nx[end] + 20, ny[end] - 20, text, B[start][end] < 100 ? 2 : 3);
        }
        else {
            MoveToEx(hdc, nx[start], ny[start], NULL);
            if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 300) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                LineTo(hdc, nx[end], ny[end]);
                TextOutA(hdc, nx[end] + xDif / 2 - 40, ny[end] - 50, text, B[start][end] < 100 ? 2 : 3);
            }
            else if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
                LineTo(hdc, nx[end], ny[end]);
                TextOutA(hdc, nx[end] - 20, ny[end] + yDif / 2 + 50, text, B[start][end] < 100 ? 2 : 3);
            }
            else if (xDif == 0 && abs(yDif) > 300) {
                LineTo(hdc, nx[end] - 30, ny[end] + yDif / 2);
                LineTo(hdc, nx[end], ny[end]);
                TextOutA(hdc, nx[end] - 40, ny[end] + yDif / 2 + 13, text, B[start][end] < 100 ? 2 : 3);
            }
            else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
                LineTo(hdc, nx[end], ny[end]);
                TextOutA(hdc, nx[end] + xDif / 2 - 20, ny[end] + yDif / 2, text, B[start][end] < 100 ? 2 : 3);
            }
            else {
                LineTo(hdc, nx[end], ny[end]);
                TextOutA(hdc, nx[end] + xDif / 5 - 20, ny[end] + yDif / 5, text, B[start][end] < 100 ? 2 : 3);
            }
        }
    }
}

void paintVertex(HDC hdc, int nx[N], int ny[N], char* nn[N], int i) {
    int dtx = 5, radius = 16;
    Ellipse(hdc, nx[i] - radius, ny[i] - radius, nx[i] + radius, ny[i] + radius);
    TextOut(hdc, nx[i] - dtx, ny[i] - 8, nn[i], 1);
}

void printMatrix(HDC hdc, int A[N][N]) {
    char text[11];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sprintf_s(text, sizeof(text), "%d", A[i][j]);
            TextOutA(hdc, 5 + 30 * j, 600 + 20 * i, text, A[i][j] < 100 ? 2 : 3);
        }
    }
}

void simMatrix(int A[N][N], int* B[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j]) {
                B[j][i] = A[i][j];
                B[i][j] = A[i][j];
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

void weightMatrix(HDC hdc, int A[N][N], int* W[N][N]) {
    int num;
    int Wt[N][N];
    int B[N][N];
    int C[N][N];
    int D[N][N];
    //Wt + B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = roundf((rand() / (float)RAND_MAX * 2) * 100) * A[i][j];
            Wt[i][j] = num;
            if (num == 0) B[i][j] = 0;
            else B[i][j] = 1;
        }
    }
    //C+D
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] != B[j][i]) C[i][j] = 1;
            else C[i][j] = 0;

            if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
            else D[i][j] = 0;
        }
    }
    //ResultMatrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Wt[i][j] = (C[i][j] + D[i][j]) * Wt[i][j];
        }
    }
    simMatrix(Wt, W);
}

int cycle(int start, int end, int visited[N], int A[N][N]) {
    if (start == end) return 1;
    if (visited[start] && visited[end]) return 1;
    return 0;
}

void prim(HDC hdc, int A[N][N], int xPos[N], int yPos[N], char* ellipseName[N], int cur) {
    int visitedEdges = 0, totalWeight = 0, start, end;
    char text[5];
    int treeMatrix[N][N] = { 0 };
    int visitedVertex[N] = { 0 };
    visitedVertex[cur] = 1;
    while (visitedEdges < N - 1) {
        int num = 200;
        for (int i = 0; i < N; i++) {
            if (!visitedVertex[i]) continue;
            for (int j = i; j < N; j++) {
                if (A[i][j] && A[i][j] < num) {
                    num = A[i][j];
                    start = i;
                    end = j;
                }
            }
        }
        if (cycle(start, end, visitedVertex, treeMatrix) && DFS(treeMatrix, start, end)) {
            A[start][end] = 0;
        }
        else {
            sprintf_s(text, sizeof(text), "%d", num);
            TextOutA(hdc, 5, 40, text, 2);
            paintLines(hdc, A, xPos, yPos, start, end);
            paintVertex(hdc, xPos, yPos, ellipseName, start);
            paintVertex(hdc, xPos, yPos, ellipseName, end);
            totalWeight += num;
            treeMatrix[start][end] = num;
            treeMatrix[end][start] = num;
            A[start][end] = 0;
            visitedVertex[start] = 1;
            visitedVertex[end] = 1;
            visitedEdges++;
            system("pause");
            system("cls");
        }
    }
    sprintf_s(text, sizeof(text), "%d", totalWeight);
    TextOutA(hdc, 5, 40, text, 3);
    //printMatrix(hdc, treeMatrix);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        int A[N][N];
        int W[N][N] = { 0 };
        int B[N][N] = {
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0}
        };
        int visited[N] = { 0,0,0,0,0,0,0,0,0,0 };
        char* nn[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        int nx[N + 1] = { 250 },
            ny[N + 1] = { 75 };

        HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));
        HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));

        SelectObject(hdc, BlackPen);

        generateMtx(A, (1.0 - 0 * 0.01 - 3 * 0.005 - 0.05));
        simMatrix(A, B);
        weightMatrix(hdc, A, W);
        //printMatrix(hdc, W);

        //Vertex coordinates
        for (int a = 0; a < N; a++) {
            if (a < 3) {
                nx[a + 1] = nx[a] + 210;
                ny[a + 1] = ny[a];
            }
            else if (a < 5) {
                nx[a + 1] = nx[a];
                ny[a + 1] = ny[a] + 210;
            }
            else if (a < 8) {
                nx[a + 1] = nx[a] - 210;
                ny[a + 1] = ny[a];
            }
            else if (a < 10) {
                nx[a + 1] = nx[a];
                ny[a + 1] = ny[a] - 210;
            }
        }

        //draw edges of the graph
        for (int start = 0; start < N; start++) {
            for (int end = start; end < N; end++) {
                paintLines(hdc, W, nx, ny, start, end);
            }
        }
        //draw verteces
        SelectObject(hdc, RedPen);
        for (int i = 0; i < N; i++) {
            paintVertex(hdc, nx, ny, nn, i);
        }

        SelectObject(hdc, GreenPen);
        prim(hdc, W, nx, ny, nn, 0);

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