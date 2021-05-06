#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define N 10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

wchar_t  ProgName[] = L"Лабораторна робота 5";

struct queue {
    int array[N];
    int front;
    int last;
};

struct queue* init() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->last = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if (q->last == -1)
        return 1;
    else
        return 0;
}

void pushQueue(struct queue* q, int value) {
    if (q->front == -1)
        q->front = 0;
    q->last++;
    q->array[q->last] = value;
}

int popQueue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    }
    else {
        item = q->array[q->front];
        q->front++;
        if (q->front > q->last) q->front = q->last = -1;
    }
    return item;
}

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
        L"LAB 5 Bondarchuk A.",
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

void paintLines(HDC hdc, int matrix[N][N], int nx[N], int ny[N], int start, int end) {
    float koef;
    int  radius = 16, divine = 1, xDif, yDif;
    if (matrix[start][end] == 1) {
        xDif = nx[start] - nx[end];
        yDif = ny[start] - ny[end];
        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
        if (start == end) {
            MoveToEx(hdc, nx[end], ny[end], NULL);
            Arc(hdc, nx[end], ny[end] - 40, nx[end] + 40, ny[end], nx[end] + 10, ny[end], nx[end], ny[end] - 10);
        } else {
            MoveToEx(hdc, nx[start], ny[start], NULL);
            if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 200) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 30);
            }   
            else if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
            }
            else if (xDif == 0 && abs(yDif) > 200) {
                LineTo(hdc, nx[end] - 30, ny[end] + yDif / 2);
            }
            else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
            }
            LineTo(hdc, nx[end], ny[end]);
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
            sprintf_s(text, 2, "%d", A[i][j]);
            TextOutA(hdc, 800 + 25 * j, 450 + 20 * i, text, 1);
        }
    }
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

//GENERATE MATRIX
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

void BFS(HDC hdc, int nx[N], int ny[N], char* nn[N], int A[N][N], int start) {//breadth
    struct queue* q = init();
    int visited[N] = { 0,0,0,0,0,0,0,0,0,0 };
    int distance[N][N] = {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 }
    };
    int treeMatrix[N][N] = {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 }
    };
    int k = 1, a = 0, dist = 0, curVertex, counter = 0;
    char text[4];
    pushQueue(q, start);
    visited[start] = 1;
    distance[dist][start] = 1;
    paintVertex(hdc, nx, ny, nn, start);
    sprintf_s(text, 2, "%d", a);
    TextOutA(hdc, nx[start] - 20, ny[start] + 15, text, 1);
    while (!isEmpty(q)) {
        curVertex = popQueue(q);
        for (int i = 0; i < N; i++) {
            if (A[curVertex][i] && visited[i] == 0) {
                k++;
                visited[i] = k;
                pushQueue(q, i);
                paintLines(hdc, A, nx, ny, curVertex, i);
                paintVertex(hdc, nx, ny, nn, i);
                system("pause");
                system("cls");
                dist = a + 1;
                distance[dist][i] = 1;
                treeMatrix[curVertex][i] = 1;
                sprintf_s(text, 2, "%d", dist);
                TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
            }
        }
        a++;
    }

    for (int i = 0;i < N; i++) {
        paintVertex(hdc, nx, ny, nn, i);
        counter = 0;
        for (int j = 0;j < N; j++) {
            if (distance[i][j]) {
                sprintf_s(text, 3, "L%d", i);
                TextOutA(hdc, 10, 550 + 25 * i, text, 2);
                sprintf_s(text, 2, "%d", j);
                TextOutA(hdc, 30 + 20 * counter, 550 + 25 * i, text, 1);
                counter++;
            }
            sprintf_s(text, 2, "%d", treeMatrix[i][j]);
            TextOutA(hdc, 10 + 10 * j, 200 + 20 * i, text, 1);
        }
    }
}

void DFS(HDC hdc, int nx[N], int ny[N], char* nn[N], int A[N][N], int start) {//depth
    int distance[N][N] = {
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 }
    };
    int treeMatrix[N][N] = {
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 }
    };
    struct stack* s = initStack();
    int visited[N] = { 0,0,0,0,0,0,0,0,0,0 };
    int k = 1, dist = 0, curVertex, counter = 0, checker = 1;
    char text[4];
    pushStack(s, start);
    visited[start] = 1;
    distance[dist][start] = 1;
    paintVertex(hdc, nx, ny, nn, start);
    sprintf_s(text, 2, "%d", dist);
    TextOutA(hdc, nx[start] - 20, ny[start] + 15, text, 1);
    while (!isEmptyStack(s)) {
        curVertex = top(s);
        for (int i = 0; i < N; i++) {
            if (A[curVertex][i]) {
                if (visited[i] == 0) {
                    k++;
                    dist++;
                    visited[i] = k;
                    distance[dist][i] = 1;
                    treeMatrix[curVertex][i] = 1;
                    pushStack(s, i);
                    paintLines(hdc, A, nx, ny, curVertex, i);
                    paintVertex(hdc, nx, ny, nn, i);
                    sprintf_s(text, 2, "%d", dist);
                    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
                    system("pause");
                    system("cls");
                    break;
                }
            }
            if (i == N - 1) {
                flush(s);
                dist--;
            }
        }
    }
    for (int i = 0;i < N; i++) {
        paintVertex(hdc, nx, ny, nn, i);
        counter = 0;
        for (int j = 0;j < N; j++) {
            if (distance[i][j]) {
                sprintf_s(text, 3, "L%d", i);
                TextOutA(hdc, 10, 450 + 25 * i, text, 2);
                sprintf_s(text, 2, "%d", j);
                TextOutA(hdc, 30 + 20 * counter, 450 + 25 * i, text, 1);
                counter++;
            }
            sprintf_s(text, 2, "%d", treeMatrix[i][j]);
            TextOutA(hdc, 10 + 10 * j, 200 + 20 * i, text, 1);
        }
    }

    for (int i = 0;i < N; i++) {
        paintVertex(hdc, nx, ny, nn, i);
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        int A[N][N];
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
        //int visited[N] = { 0,0,0,0,0,0,0,0,0,0 };
        char* nn[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        int nx[N + 1] = { 350 },
            ny[N + 1] = { 100 };

        HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));
        HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));


        SelectObject(hdc, BlackPen);

        generateMtx(A, (1.0 - 0 * 0.01 - 3 * 0.005 - 0.15));
        simMatrix(A, B);
        printMatrix(hdc, B);

        //Vertex coordinates
        for (int a = 0; a < N; a++) {
            if (a < 3) {
                nx[a + 1] = nx[a] + 110;
                ny[a + 1] = ny[a];
            }
            else if (a < 5) {
                nx[a + 1] = nx[a];
                ny[a + 1] = ny[a] + 110;
            }
            else if (a < 8) {
                nx[a + 1] = nx[a] - 110;
                ny[a + 1] = ny[a];
            }
            else if (a < 10) {
                nx[a + 1] = nx[a];
                ny[a + 1] = ny[a] - 110;
            }
        }

        //draw edges of the graph
        for (int start = 0; start < N;start++) {
            for (int end = start; end < N;end++) {
                paintLines(hdc, B, nx, ny, start, end);
            }
        }
        //draw verteces
        SelectObject(hdc, RedPen);
        for (int i = 0;i < N;i++) {
            paintVertex(hdc, nx, ny, nn, i);
        }

        //Breadth
        SelectObject(hdc, GreenPen);
        //BFS(hdc, nx, ny, nn, B, 4);

        //Depth
        DFS(hdc, nx, ny, nn, B, 3);

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