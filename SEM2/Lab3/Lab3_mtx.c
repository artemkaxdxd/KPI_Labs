#include <stdio.h>
#include <windows.h>
#define n 10

int** randMatrix(float k) {
    srand(0503);
    int matrix[n][n];
    float num;
    int element;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            num = (rand() / (float)RAND_MAX * 2) * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
            printf("%d ", element);
        }
        printf("\n");
    }
    return matrix;
}

int main()
{
    float koef = (1.0 - 0 * 0.02 - 3 * 0.005 - 0.25);
    randMatrix(koef);
    return 0;
}