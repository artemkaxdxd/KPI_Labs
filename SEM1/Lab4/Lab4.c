#include <stdio.h>

#define M 10
#define N 8

int matrix[M][N] = {
        {  0, 3, 6, 9, 12, 16, 19, 22 },
        {  0, 3, 6, 9, 12, 16, 19, 22 },
        {  0, 3, 6, 8, 12, 16, 19, 22 },
        { -1, 3, 5, 8, 12, 15, 18, 21 },
        { -1, 2, 5, 8, 11, 15, 18, 21 },
        { -1, 2, 5, 8, 11, 14, 18, 21 },
        { -1, 2, 5, 7, 11, 14, 17, 20 },
        { -2, 1, 4, 7, 10, 14, 17, 20 },
        { -2, 1, 4, 7, 10, 13, 17, 20 },
        { -2, 1, 4, 7, 10, 13, 17, 20 } };

int main(void) {
    for (int R = 0; R < M; R++) {
        for (int C = 0; C < N; C++) {
            printf("%d ", matrix[R][C]);
        }
        printf("\n");
    }
    int col = 0, key;
    printf("\nInput your key: ");
    scanf_s("%d", &key);
    while (col < N) {
        int low = 0, high = 9, mid = (low + high) / 2;
        while (low <= high) {
            if (matrix[mid][col] == key) {
                printf("Found key at coord [%d, %d]\n", col, mid);
                break;
            }
            else if (matrix[mid][col] > key) {
                low = mid + 1;
            }
            else if (matrix[mid][col] < key) {
                high = mid - 1;
            }
            mid = (low + high) / 2;
        }
        col++;
    }
    return 0;
}